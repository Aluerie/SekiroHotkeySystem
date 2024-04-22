# 🍴 Fork Extra Info

This Fork changes behavior of the mod to the following way:

* When you press keys `Combat Art 1`, `Combat Art 2`, ... - you no longer immediately equip the item but rather show a preference that will be used with `Combat Art Key` as described below:
* It changes the behaviour of the `Combat Art Key` (the one that does Combat Art motion in one click):
    * When you hold your `Combat Art Key` down - it equips the combat art chosen with previous keys;
    * When you let `Combat Art Key` up - it unequips the combat art;

This way you cannot accidentally press Combat Art.

Video Showcase (note how combat icon in the corner fades away and how it doesn't use combat art when I press RMB+LMB in the end):

<https://github.com/Aluerie/SekiroHotkeySystem/assets/33165440/93953574-faeb-4cad-8399-3ba6c316268e>

## ⚠️ Disclaimer

* I tried to fork two similar projects:
    * Weapon Wheel - [Aluerie/Sekiro-ShiftCombatArt](<https://github.com/Aluerie/Sekiro-ShiftCombatArt>)
    * HotkeySystem - current repo.
* However, both repos have the some annoying bugs.
    * To be honest, there is less bugs when using the mod provided with the other fork (but the code in it is also quite messy as well).
    * Other note, is that even base mods have most of those bugs because it was intended by Fromsoft to be able to swap combat arts on the fly.

# Parent repo ReadME

![img](https://i.imgur.com/7UD9s3t.png)

# Sekiro Hotkey System

Hotkey system for Sekiro to allow seamlessly switching between combat arts and prosthetics.

### [Support Discord](https://discord.gg/5FaCGrFYM3)

## Installation

Download the files from the release section [here](https://github.com/ReaperAnon/SekiroHotkeySystem/releases/download/main/release.7z), then place all the files in the archive into your Sekiro game folder (near where sekiro.exe is located).

### If you get prompted to overwrite dinput8.dll

In case you have another mod that relies on the same DLL file you will have to chainload the mods. You can do this in either direction (as in loading the other mod with sekiro hotkey system or vice-versa).

Sometimes one way or the other causes a crash on game start so if it doesn't work just try it the other way around before reporting an issue.

**To chainload the mods either check the other mod's description on how to do so or do the following:** Rename the dinput8.dll that is already in your game folder to something else (for example, if it comes from the sekiro mod engine you could rename it to "modengine.dll") and then install this mod as instructed without having to replace any files.

After this, navigate to the "configs" folder that you just placed into your game folder and open the chainload.ini file with a text editor. Now simply add the name of the other dll between the quotation marks (like modengine.dll for example) and save it.
That's it, now your game should load both mods just fine without issues.

## Functionality

Once you are in-game, when opening the pause menu you will see a button at the top, simply click it or press Tab to open it. There are detailed tooltips explaining every functio and option (they are also named in intuitive ways so easy to figure out).

I'll expand this section once I get back to the mod and clean up the configuration functionality a bit (I really just threw that together). Also going to make a more comprehensive video on how it all works, but here are a couple I made on an older version during development that should be enough for now.

[![Vid1](https://img.youtube.com/vi/DObp2otd7ic/sddefault.jpg)](https://www.youtube.com/watch?v=DObp2otd7ic)

[![Vid2](https://img.youtube.com/vi/stx7W0il18c/sddefault.jpg)](https://www.youtube.com/watch?v=stx7W0il18c)

## Credits

#### tmsrise - Sharing some important functions he found so I could get the configuration menu working nicely

#### TsudaKageyu - MinHook

#### CreamyRaccoon - Testing

#### Dolphin - Existing

#### ImGui

#### NotoSans Font
