
# GladiatorArena - Unreal Engine 5.6 Project

This project is a gladiator-style arena fighting game built in Unreal Engine 5.6, designed for both single-player and multiplayer modes. It features character creation, permadeath with revival mechanics, a gear shop, and both asynchronous matchmaking and competitive PvP combat.

---

## 🎮 Game Overview

- **Genre:** Arena Fighter / Action RPG
- **Engine:** Unreal Engine 5.6 (C++ + Blueprints)
- **Modes:** Single-player, Async Multiplayer, 2v2 Competitive PvP

---

## ✅ Project Setup (Codex Instructions)

### 🧱 Step 1: Create Project

- Template: Games → Blank
- Project Type: C++ with Starter Content
- Target Platform: Desktop/Console
- Name: `GladiatorArena`

---

### 📁 Step 2: Folder Structure

Create these folders in `/Content/`:

```
/Blueprints
/Characters/Player
/Weapons
/Maps
/GameModes/MainMenu
/GameModes/Arena
/GameModes/CharacterCreate
/Systems/GameInstance
/Systems/Player
/HUD
/UI/Widgets
/Data
/FX
/Animations
/Materials
/Multiplayer
```

---

### 🧠 Step 3: Core C++ Classes

Create and implement these C++ classes with stub logic:

- `GI_GladiatorCore` → inherits `UGameInstance`
- `GM_MainMenu` → inherits `AGameModeBase`
- `GM_ArenaCombat` → inherits `AGameModeBase`
- `GM_CharacterCreate` → inherits `AGameModeBase`
- `PC_Player` → inherits `APlayerController`
- `PS_Player` → inherits `APlayerState`
- `HUD_Base` → inherits `AHUD`

**GI_GladiatorCore.cpp**
```cpp
void UGI_GladiatorCore::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("GI_GladiatorCore Initialized"));
}
```

---

### ⚙️ Step 4: Project Settings

Assign the custom classes in Project Settings:

- Game Instance Class → `GI_GladiatorCore`
- Default Game Mode → `GM_MainMenu`
- Player Controller Class → `PC_Player`
- Player State Class → `PS_Player`
- HUD Class → `HUD_Base`

---

## 🚀 Planned Game Features

### 1. Main Menu
- New Character, Load Character (grayed out if none), Settings, Exit

### 2. Character System
- 2 starting slots
- Fallen gladiators sent to infirmary
- Slot locks with timer
- Revive via money or sacrifice

### 3. Shop
- Buy gear and weapons
- Unlocks tied to progression

### 4. Combat
- Arena melee
- Stamina, injury, weapons, equipment

### 5. Multiplayer
- Async Mode (Clash of Clans style)
- Competitive 2v2 PvP live matchmaking

---

## 🔁 Multiplayer Requirements

- All gameplay systems must be multiplayer-compatible
- Full replication (`bReplicates = true`) for actors
- Authority logic must be server-side
- Local SaveGame can sync with backend later

---

Project is ready for continued development after compiling these initial classes.
