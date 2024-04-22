#include <combatarts.h>

int CAFunctions::CAUsageMode = 0;

bool CAFunctions::UseWhileBlocking = false;

bool CAFunctions::UseWhileInAir = false;

bool CAFunctions::UseOnRepeat = false;

int CAFunctions::CombatArtSize = 0;

std::vector<unsigned> CAFunctions::CombatArts;

bool IsCombatArtThreadRunning = false;

// # FORK ADDITIONS START HERE #
short currentCAIdx = 0;
bool IsChooseCombatArtThreadRunning = false;
bool IsEquipCombatArtThreadRunning = false;
bool IsUnequipCombatArtThreadRunning = false;

bool IsForkCombatArtThreadRunning = false;
// # FORK ADDITIONS END HERE #

unsigned SkillEquipData[17];

// Array Manipulation
void CAFunctions::PerformArraySetup(const unsigned length)
{
    CombatArts.resize(length);
}

bool CAFunctions::IsArrayEmpty()
{
    unsigned result = 0;
    for (const auto &entry : CombatArts)
        result += entry;

    return result == 0;
}

void CAFunctions::ClearEquipmentSlots()
{
    size_t length = CombatArts.size();
    CombatArts.clear();
    CombatArts.resize(length);
    WidgetMenu::CombatArtNames.clear();
}

// Combat Art Functionality
void CAFunctions::PerformArt(bool wasChanged)
{
    Input::SekiroInputAction attackAction = Input::SIA_Attack;
    Input::SekiroInputAction combatArtAction = Input::SIA_CombatArt;
    if (CAUsageMode == 1 || (UseOnRepeat && !wasChanged))
    {
        Input::AddLongPressInput(&combatArtAction);
        return;
    }

    if (UseWhileBlocking)
    {
        if (Input::IsInputActive(Input::SIA_Block))
        {
            Input::AddLongPressInput(&attackAction);
            return;
        }
    }

    if (UseWhileInAir)
    {
        bool isInAir = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0x249) & 2;
        if (isInAir)
        {
            Input::AddLongPressInput(&combatArtAction);
            return;
        }
    }
}

void CAFunctions::TrySelectCombatArt(void *idx)
{
    if (!IsCombatArtThreadRunning)
        std::thread(QueueSelectCombatArt, idx).detach();
}

void CAFunctions::QueueSelectCombatArt(void *idx)
{
    IsCombatArtThreadRunning = true;
    while (!SelectCombatArt(idx))
        Sleep(20);

    IsCombatArtThreadRunning = false;
}

bool CAFunctions::SelectCombatArt(void *idx)
{
    bool result = true;
    uint64_t skillBase = Hooks::GetSkillBase();

    if (skillBase == 0) // exit if not in-game
        return false;

    short caIdx = *reinterpret_cast<short *>(idx);
    unsigned currentMenuID = *reinterpret_cast<unsigned *>(skillBase + 0x28);
    if (Hooks::IsInMenu() || CombatArts[caIdx] == 0)
    {
        CombatArts[caIdx] = currentMenuID;
        Hooks::PlayUISound(MENU_SUBLIST_SELECT_CLOSE);
        WidgetMenu::UpdateCombatArtNames();
    }
    else
    {
        bool wasChanged = false;
        if (currentMenuID != CombatArts[caIdx])
        {
            wasChanged = true;
            SkillEquipData[16] = 0;
            SkillEquipData[14] = CombatArts[caIdx];
            result = Hooks::SetSkillSlot(1, reinterpret_cast<uint64_t>(SkillEquipData), true) != 0;
            if (result)
                Hooks::PlayUISound(MENU_OPTIONS_CHANGE);
        }
        else
            Hooks::PlayUISound(MENU_HIGHLIGHT);

        // # FORK ADDITIONS START HERE #
        // PerformArt(wasChanged); // this causes many bugs so let's turn it off
        // # FORK ADDITIONS END HERE #
    }

    return result;
}

// # FORK ADDITIONS START HERE #

// #####################
// # CHOOSE COMBAT ART #
// #####################

void CAFunctions::TryChooseCombatArt(void *idx)
{
    if (!IsChooseCombatArtThreadRunning)
        std::thread(QueueChooseCombatArt, idx).detach();
}

void CAFunctions::QueueChooseCombatArt(void *idx)
{
    IsChooseCombatArtThreadRunning = true;
    while (!ChooseCombatArt(idx))
        Sleep(20);

    IsChooseCombatArtThreadRunning = false;
}

bool CAFunctions::ChooseCombatArt(void *idx)
{
    bool result = true;
    uint64_t skillBase = Hooks::GetSkillBase();

    if (skillBase == 0) // exit if not in-game
        return false;

    currentCAIdx = *reinterpret_cast<short *>(idx);

    short caIdx = currentCAIdx;
    unsigned currentMenuID = *reinterpret_cast<unsigned *>(skillBase + 0x28);
    if (Hooks::IsInMenu() || CombatArts[caIdx] == 0)
    {
        CombatArts[caIdx] = currentMenuID;
        Hooks::PlayUISound(MENU_SUBLIST_SELECT_CLOSE);
        WidgetMenu::UpdateCombatArtNames();
    }
    else
    {
        bool wasChanged = false;
        if (currentMenuID != CombatArts[caIdx])
        {
            wasChanged = true;
        }
    }

    return result;
}

// #########
// # EQUIP #
// #########

void CAFunctions::TryEquipCombatArt(void *idx)
{
    if (!IsForkCombatArtThreadRunning)
        std::thread(QueueEquipCombatArt, idx).detach();
}

void CAFunctions::QueueEquipCombatArt(void *idx)
{
    IsForkCombatArtThreadRunning = true;
    while (!EquipCombatArt())
        Sleep(25);

    IsForkCombatArtThreadRunning = false;
}

bool CAFunctions::EquipCombatArt()
{
    bool result = true;
    uint64_t skillBase = Hooks::GetSkillBase();

    if (skillBase == 0) // exit if not in-game
        return false;

    short caIdx = currentCAIdx;
    unsigned currentMenuID = *reinterpret_cast<unsigned *>(skillBase + 0x28);
    if (Hooks::IsInMenu() || CombatArts[caIdx] == 0)
    {
        CombatArts[caIdx] = currentMenuID;
    }
    else
    {
        bool wasChanged = false;
        if (currentMenuID != CombatArts[caIdx])
        {
            wasChanged = true;
            SkillEquipData[16] = 0;
            SkillEquipData[14] = CombatArts[caIdx];
            result = Hooks::SetSkillSlot(1, reinterpret_cast<uint64_t>(SkillEquipData), true) != 0;
        }
    }

    return result;
}

// ###########
// # UNEQUIP #
// ###########

void CAFunctions::TryUnequipCombatArt(void *idx)
{
    if (!IsForkCombatArtThreadRunning)
        std::thread(QueueUnequipCombatArt, idx).detach();
}

void CAFunctions::QueueUnequipCombatArt(void *idx)
{
    IsForkCombatArtThreadRunning = true;
    while (!UnequipCombatArt())
        Sleep(25);

    IsForkCombatArtThreadRunning = false;
}

bool CAFunctions::UnequipCombatArt()
{
    bool result = false;
    uint64_t skillBase = Hooks::GetSkillBase();

    if (skillBase == 0) // exit if not in-game
        return false;

    uint64_t EquipInventoryDataPtr = Hooks::GetEquipInventoryData();
    if (!Hooks::IsInMenu())
    {
        SkillEquipData[16] = 0;
        unsigned int emptyArtID = 5000;
        SkillEquipData[14] = Hooks::GetMenuID(EquipInventoryDataPtr + 0x10, &emptyArtID);

        // comments might be totally wrong
        int animation1 = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0x248); // air-related combat art like Sakura dance
        int animation2 = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0xD8);
        int animation3 = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0x249); // 01 - standing on earth, 03 - jump, 08 - grapple
        int animation4 = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0x1B4); // 1 when we do combat related action
        int animation5 = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0xe4);  // 1 when combat related action
        int animation6 = *reinterpret_cast<byte *>(Hooks::GetInputHandler() + 0xb8);  // adds +10 (so 4th bit in 10001000) when animation flicks to stationary but only once i.e. we jump up, it will turn +10 for a moment when we land.

        int animationID = Hooks::GetCurrentAnimation();

        bool idk = (animationID == 790040);
        bool idk2 = (animationID == 790010);

        bool isGroundSpecialAttackCombo1 = (animationID == 106316000);
        bool isGroundSpecialAttackCombo1Re = (animationID == 106316100);
        bool isGroundSpecialAttackCombo2 = (animationID == 106316010);
        bool isGroundSpecialAttackCombo2Re = (animationID == 106316110);

        bool isAirSpecialAttack = (animationID == 106316200);
        bool isLandAirSpecialAttack = (animationID == 106316210);

        bool force = (!(idk ||
                        //    idk2 ||
                        isGroundSpecialAttackCombo1 ||
                        isGroundSpecialAttackCombo1Re ||
                        isGroundSpecialAttackCombo2 ||
                        isGroundSpecialAttackCombo2Re ||
                        isAirSpecialAttack ||
                        isLandAirSpecialAttack) &&
                      ((animation4 == 1) && (animation5 == 1)));
        // if (force) // didn't help lol
        // {
        //     Sleep(500);
        // }
        result = Hooks::SetSkillSlot(1, reinterpret_cast<uint64_t>(SkillEquipData), force) != 0;
        return result;
    }
    return false;
}

// # FORK ADDITIONS END HERE #