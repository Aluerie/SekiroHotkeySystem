#pragma once

#include <vector>
#include <thread>
#include <data.h>
#include <functions.h>
#include <widget_menu.h>
#include <input_injection.h>

namespace CAFunctions
{
	extern int CAUsageMode;

	extern bool UseWhileBlocking;

	extern bool UseWhileInAir;

	extern bool UseOnRepeat;

	extern int CombatArtSize;

	extern std::vector<unsigned> CombatArts;

	void PerformArraySetup(const unsigned length);

	bool IsArrayEmpty();

	void ClearEquipmentSlots();

	void PerformArt(bool wasChanged);

	void TrySelectCombatArt(void *idx);

	void QueueSelectCombatArt(void *idx);

	bool SelectCombatArt(void *idx);

	// # FORK ADDITIONS START HERE #

	// Choose
	void TryChooseCombatArt(void *idx);

	void QueueChooseCombatArt(void *idx);

	bool ChooseCombatArt(void *idx);

	// Equip
	void TryEquipCombatArt(void *idx);

	void QueueEquipCombatArt(void *idx);

	bool EquipCombatArt();

	// Unequip
	void TryUnequipCombatArt(void *idx);

	void QueueUnequipCombatArt(void *idx);

	bool UnequipCombatArt();

	// # FORK ADDITIONS END HERE #
}