# GOG EXE + PDB Summary

Headless analysis performed with `pyghidra` / `pyghidra_mcp` plus direct RSDS/MSF parsing.

## Inputs

- EXE: `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- PDB: `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb`

## Debug Metadata

- EXE RSDS record:
  - GUID: `04ffcabe-6837-4ab9-9d42-e5b9df4c7cba`
  - Age: `1`
  - Expected PDB path: `D:\code\BattleZoneTest\build\bin\Release\battlezone\battlezone98redux.pdb`
- Provided PDB info stream:
  - GUID: `37614db0-6577-4506-8ad6-0e6a72f6fd2f`
  - Age: `1`
  - Signature: `0x571544EF`
  - Version: `0x01312E94`
- Match status: `MISMATCH`

## PDB Evidence That Still Helps

- BattleZoneTest source or object paths found in the PDB:
  - `E:\BattleZoneTest\source`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\vc120.pdb`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\i76common.pch`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\audio.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\cb.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\directsound_theoraaudiointerface.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\redbook.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\d3dapp.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\D3ddebug.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\D3dpoly.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\D3drendr.obj`
  - `E:\BattleZoneTest\build\obj\Release\battlezone\carclsn.obj`

### Map UI and filters

- `cMapManager::BuildFilteredMapList`
- `*E:\BattleZoneTest\build\obj\Release\battlezone\UI_Multiplayer_Create.obj`
- `cUI_Multiplayer_Create::FilterSelected`
- `cUI_Multiplayer_Create::MapFilterToggle`
- `*E:\BattleZoneTest\build\obj\Release\battlezone\UI_Multiplayer_MapSelect.obj`
- `cUI_Multiplayer_MapSelect::FilterMaps`
- `HPE:\BattleZoneTest\build\obj\Release\battlezone\filters.obj`
- `E:\BattleZoneTest\build\obj\Release\battlezone\UI_Multiplayer_Create.obj`
- `E:\BattleZoneTest\build\obj\Release\battlezone\UI_Multiplayer_MapSelect.obj`
- `E:\BattleZoneTest\build\obj\Release\battlezone\filters.obj`

### Lobby and chat

- `CSteamLobby::GetCurrentLobby`
- `CSteamLobby::GetCurrentUser`
- `NetPlayer::NotifyLeftLobby`
- `HPE:\BattleZoneTest\build\obj\Release\battlezone\chat.obj`
- `*E:\BattleZoneTest\build\obj\Release\battlezone\lobby.obj`
- ``CSteamLobby::OnChatMessage'::`2'::`dynamic atexit destructor for 'assignTag''`
- ``CSteamLobby::OnChatMessage'::`2'::`dynamic atexit destructor for 'kickTag''`
- ``CSteamLobby::OnChatMessage'::`2'::`dynamic atexit destructor for 'pmTag''`
- ``CSteamLobby::OnChatMessage'::`2'::`dynamic atexit destructor for 'updateTag''`
- `CSteamLobby::KickUser`
- `CSteamLobby::OnChatMessage`
- ``CSteamLobby::OnChatMessage'::`2'::kickTag`
- `CSteamLobby::OnLobbyChatUpdate`
- `CSteamLobby::OnLobbyKicked`
- `*E:\BattleZoneTest\build\obj\Release\battlezone\UI_MultiPlayer_Lobby.obj`
- `E:\BattleZoneTest\build\obj\Release\battlezone\chat.obj`
- `E:\BattleZoneTest\build\obj\Release\battlezone\lobby.obj`
- `E:\BattleZoneTest\build\obj\Release\battlezone\UI_MultiPlayer_Lobby.obj`

### User bar and mute or whisper UI

- `*E:\BattleZoneTest\build\obj\Release\battlezone\UI_UserBar.obj`
- `cUI_UserBar::cUI_UserBar`
- `gClick_UserBar_Kick`
- `gClick_UserBar_Msg`
- `gClick_UserBar_Mute`
- `cUI_UserBar::msgCB`
- `cUI_UserBar::muteCB`
- `?gClick_UserBar_Mute@@YAXXZ`
- `?gClick_UserBar_Kick@@YAXXZ`
- `?gClick_UserBar_Msg@@YAXXZ`
- `E:\BattleZoneTest\build\obj\Release\battlezone\UI_UserBar.obj`

### Lobby slash commands

- `Net_KickPlayer`
- `Net_LockGame`
- `Net_MutePlayer`
- `Net_UnlockGame`
- `Net_UnmutePlayer`
- `_Net_KickPlayer`
- `_Net_UnlockGame`
- `_Net_LockGame`
- `_Net_UnmutePlayer`
- `_Net_MutePlayer`

## Ghidra Function Snapshots

### Multiplayer create screen root

- Address: `0x00796880`
- Signature: `void __fastcall FUN_00796880(undefined4 *param_1);`
- PDB hints:
  - `cUI_Multiplayer_Create::cUI_Multiplayer_Create`
  - `UI_Multiplayer_Create.obj`
```c
void __fastcall FUN_00796880(undefined4 *param_1)

{
  undefined1 uVar1;
  char cVar2;
  undefined4 uVar3;
  void *pvVar4;
  int *piVar5;
  int iVar6;
  char *_Str;
  uint uVar7;
  longlong lVar8;
  undefined4 uVar9;
  undefined1 *puVar10;
  int *local_1f8;
  int *local_1e8;
  int *local_1e4;
  undefined4 local_1d8;
  undefined4 local_1d4;
  int *local_1d0;
  undefined4 local_1c8;
  undefined4 local_1b8;
  undefined4 local_1a8;
  undefined4 local_198;
  undefined4 local_188;
  undefined4 local_16c;
  undefined4 local_168;
  int *local_164;
  undefined4 local_158;
  int *local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_fc;
  undefined4 local_f8;
  int *local_f4;
  int *local_ec;
  undefined4 local_e8;
  int *local_d8;
  int *local_c4;
  uint local_b8;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [48];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f578;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0();
  local_8 = 0;
  *param_1 = cUI_Multiplayer_Create::vftable;
  vector<>();
  local_8._0_1_ = 1;
  FUN_005df1f0();
  lVar8 = FUN_00822ea0();
  *(longlong *)(param_1 + 0x52) = lVar8 + 500;
  uVar3 = FUN_00764760();
  param_1[0x6f] = uVar3;
  uVar1 = FUN_00742cf0();
  *(undefined1 *)(param_1 + 0x75) = uVar1;
  *(undefi
```

### Map filter gate

- Address: `0x00752A50`
- Signature: `void FUN_00752a50(void);`
- PDB hints:
  - `cUI_Multiplayer_MapSelect::FilterMaps`
  - `cMapManager::BuildFilteredMapList`
  - `filters.obj`
```c
void FUN_00752a50(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c148;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00752ed0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  puVar4 = local_2c;
  FUN_00764790(puVar4);
  FUN_004bb540(puVar4);
  local_8._0_1_ = 1;
  do {
    puVar4 = local_38;
    FUN_00764790(puVar4);
    local_20 = FUN_004bb570(puVar4);
    local_8._0_1_ = 2;
    local_1c = local_20;
    local_11 = FID_conflict_operator<(local_20);
    local_8._0_1_ = 1;
    FUN_004bb3b0();
    if (local_11 == '\0') {
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004bb3b0();
      local_8 = 0xffffffff;
      ~basic_string<>();
      ExceptionList = local_10;
      return;
    }
    cVar1 = FUN_00427270(&stack0x00000004,"All Maps");
    if (cVar1 == '\0') {
      cVar1 = FUN_00427270(&stack0x00000004,"Strategy");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'S') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Strategy");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'M') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Death Match");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'D') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Death Match");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'A') goto LAB_00752cc4;
      }
      cVar1 =
```

### Map filter list rebuild

- Address: `0x007A3160`
- Signature: `void FUN_007a3160(undefined4 param_1,undefined4 param_2);`
- PDB hints:
  - `cUI_Multiplayer_Create::MapFilterToggle`
  - `cUI_Multiplayer_Create::FilterSelected`
  - `UI_Multiplayer_Create.obj`
```c
void FUN_007a3160(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  uint uVar4;
  undefined4 uVar5;
  float10 fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 local_1fc;
  undefined4 local_1f8;
  undefined4 local_1f0;
  undefined4 local_1e4;
  undefined4 local_1d8;
  undefined4 local_1d4;
  uint local_1d0;
  char local_1c9;
  int local_1c8;
  undefined1 local_1c4 [24];
  undefined1 local_1ac [24];
  undefined1 local_194 [24];
  undefined1 local_17c [24];
  undefined1 local_164 [24];
  undefined1 local_14c [24];
  undefined1 local_134 [24];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008602fc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  vector<>(local_14);
  local_8 = 0;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  FUN_00764790();
  local_1c9 = FUN_00767fe0();
  basic_string<>("All Maps");
  local_8._0_1_ = 3;
  FUN_006cf320(local_74);
  local_8._0_1_ = 2;
  ~basic_string<>();
  iVar1 = FUN_004344a0();
  if (iVar1 != 2) {
    basic_string<>("Strategy");
    local_8._0_1_ = 4;
    FUN_006cf320(local_a4);
    local_8._0_1_ = 2;
    ~basic_string<>();
  }
  basic_string<>("Death Match");
  local_8._0_1_ = 5;
  FUN_006cf320(local_134);
  local_8._0_1_ = 2;
  ~basic_s
```

### Map list viewport update

- Address: `0x007997A0`
- Signature: `void __fastcall FUN_007997a0(int param_1);`
- PDB hints:
  - `cUI_Multiplayer_MapSelect`
  - `UI_Multiplayer_MapSelect.obj`
```c
void __fastcall FUN_007997a0(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  
  uVar1 = FUN_007d3360();
  (**(code **)(**(int **)(param_1 + 0x168) + 0x24))(uVar1);
  uVar1 = FUN_007d3360();
  (**(code **)(**(int **)(param_1 + 0x17c) + 0x24))(uVar1);
  cVar2 = FUN_007d3360();
  (**(code **)(**(int **)(param_1 + 0x164) + 0x24))(cVar2 == '\0');
  uVar1 = FUN_007d3360();
  FUN_007a3c30(uVar1);
  uVar1 = FUN_007d3360();
  FUN_007cc5c0(uVar1);
  return;
}
```

### Map selection wrapper

- Address: `0x00799880`
- Signature: `void __fastcall FUN_00799880(int param_1);`
- PDB hints:
  - `cUI_Multiplayer_MapSelect`
  - `UI_Multiplayer_MapSelect.obj`
```c
void __fastcall FUN_00799880(int param_1)

{
  undefined4 uVar1;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f5f0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_007cb0c0(local_14);
  (**(code **)(**(int **)(param_1 + 0x16c) + 0x3c))(uVar1);
  FUN_007997a0();
  basic_string<>();
  local_8 = 0;
  uVar1 = FUN_007cb0c0();
  basic_string<>(uVar1);
  local_8._0_1_ = 1;
  FUN_007a4460(local_2c,local_44);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}
```

### Map selection restore helper

- Address: `0x007CAFA0`
- Signature: `void __thiscall FUN_007cafa0(int param_1,undefined4 param_2);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
  - `cUI_Multiplayer_MapSelect`
```c
void __thiscall FUN_007cafa0(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  uint local_c;
  
  local_c = 0;
  while( true ) {
    uVar4 = size();
    if (uVar4 <= local_c) break;
    puVar5 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar5 + 0x24))(0);
    local_c = local_c + 1;
  }
  *(undefined4 *)(param_1 + 0x14c) = param_2;
  cVar3 = FUN_007d3360();
  if ((cVar3 != '\0') && (*(int *)(param_1 + 0x14c) != -1)) {
    iVar1 = *(int *)(param_1 + 0x14c);
    iVar2 = *(int *)(param_1 + 0x150);
    iVar6 = size();
    if ((iVar1 - iVar2 < iVar6) && (*(int *)(param_1 + 0x150) <= *(int *)(param_1 + 0x14c))) {
      puVar5 = (undefined4 *)FUN_004200d0(*(int *)(param_1 + 0x14c) - *(int *)(param_1 + 0x150));
      (**(code **)(*(int *)*puVar5 + 0x24))(1);
    }
  }
  return;
}
```

### Map scroll down helper

- Address: `0x007CB500`
- Signature: `void __fastcall FUN_007cb500(int param_1);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
  - `cUI_Multiplayer_MapSelect`
```c
void __fastcall FUN_007cb500(int param_1)

{
  if (0 < *(int *)(param_1 + 0x150)) {
    *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + -1;
    FUN_007cb400();
  }
  return;
}
```

### Map scroll up helper

- Address: `0x007CB540`
- Signature: `void __fastcall FUN_007cb540(int param_1);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
  - `cUI_Multiplayer_MapSelect`
```c
void __fastcall FUN_007cb540(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0066b150();
  iVar2 = size();
  if (*(int *)(param_1 + 0x150) < iVar1 - iVar2) {
    *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + 1;
    FUN_007cb400();
  }
  return;
}
```

### User bar constructor / whisper + mute buttons

- Address: `0x007D0770`
- Signature: `undefined4 * __thiscall FUN_007d0770(undefined4 *param_1,undefined4 param_2,undefined4 param_3,float param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,char param_8);`
- PDB hints:
  - `cUI_UserBar::cUI_UserBar`
  - `cUI_UserBar::msgCB`
  - `cUI_UserBar::muteCB`
  - `UI_UserBar.obj`
```c
undefined4 * __thiscall
FUN_007d0770(undefined4 *param_1,undefined4 param_2,undefined4 param_3,float param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,char param_8)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 local_38;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008629b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_1[3] = param_5;
  param_1[5] = param_7;
  param_1[4] = param_6;
  if (param_8 == '\x01') {
    param_4 = param_4 + 48.0;
  }
  DAT_009456d0 = param_1;
  pvVar2 = operator_new(0x1ec);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_007c2480("Whisper User",param_3,param_4,0x42400000,0x42400000,0x20,param_2,0,0);
  }
  local_8 = 0xffffffff;
  *param_1 = local_20;
  FUN_007d2870("MultiplayerModeButton_off.png");
  (**(code **)(*(int *)*param_1 + 0x40))("MultiplayerModeButton_over.png",uVar1);
  (**(code **)(*(int *)*param_1 + 0x3c))("MultiplayerModeButton_on.png");
  uVar3 = FUN_0081cb40("first_letter","whisper");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_007d06e0);
  FUN_007c23c0(FUN_007d0710);
  FUN_007d2110(*param_1,0);
  pvVar2 = operator_new(0x1ec);
  local_8 = 1;
  if (pvVar2 == (void *)0x0) {
    local_28 = 0;
  }
  else {
    local_28 = FUN_007c2480("Mute User",param_3,param_4 + 48.0,0x42400000,0x42400000,0x20,param_2,0,
                            0);
  }
  local_8 = 0xffffffff;
  param_1[1] = local_28;
  FUN_007d2870("MultiplayerModeButton_off.png");
  (**(code **)(*(int *)param_1[1] + 0x40))("MultiplayerModeB
```

### Lobby slash command handler

- Address: `0x006247A0`
- Signature: `void FUN_006247a0(ushort param_1,char *param_2);`
- PDB hints:
  - `Net_MutePlayer`
  - `Net_UnmutePlayer`
  - `Net_KickPlayer`
  - `Net_LockGame`
  - `Net_UnlockGame`
```c
void FUN_006247a0(ushort param_1,char *param_2)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *local_538;
  char *local_530;
  char *local_52c;
  char *local_528;
  char *local_520;
  short local_518;
  short local_510;
  undefined2 local_508;
  char local_506 [1022];
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00823330(DAT_02a1748c,0);
  FUN_00823390(DAT_02a1748c,0);
  FUN_00821310(DAT_00920168,1,1);
  if (((param_2 != (char *)0x0) && (*param_2 != '\0')) && (iVar3 = FUN_00572a70(), iVar3 != 0)) {
    iVar3 = _stricmp(param_2,"/help");
    if (iVar3 == 0) {
      FUN_00821390(DAT_00920168,"/mute <player> - mute the specified player");
      FUN_007a47b0(0,"/mute <player> - mute the specified player");
      FUN_00821390(DAT_00920168,"/unmute <player> - unmute the specified player");
      FUN_007a47b0(0,"/unmute <player> - unmute the specified player");
      FUN_00821390(DAT_00920168,"/kick <player> - kick out the specified player");
      FUN_007a47b0(0,"/kick <player> - kick out the specified player");
      FUN_00821390(DAT_00920168,"/lock - prevent new players from joining");
      FUN_007a47b0(0,"/lock - prevent new players from joining");
      FUN_00821390(DAT_00920168,"/unlock - allow new players to join");
      FUN_007a47b0(0,"/unlock - allow new players to join");
    }
    else {
      iVar3 = _stricmp(param_2,"/kick");
      if (iVar3 == 0) {
        iVar3 = FUN_00572a60();
        if (iVar3 == 0) {
          uVar4 = FUN_0081cb40("multi_message","only_host_kick");
          FUN_00624710(uVar4);
        }
        else if (param_1 != 0) {
          uVar4 = FUN_005779d0(param_1);
          uVar5 = FUN_0081cb40("multi_message","kicked",uVar4);
```

### Lobby chat update callback

- Address: `0x0073EEB0`
- Signature: `void FUN_0073eeb0(undefined4 param_1,undefined4 param_2,int param_3,char param_4,char param_5,char param_6);`
- PDB hints:
  - `CSteamLobby::OnLobbyChatUpdate`
  - `CSteamLobby::OnChatMessage`
  - `lobby.obj`
  - `chat.obj`
```c
void FUN_0073eeb0(undefined4 param_1,undefined4 param_2,int param_3,char param_4,char param_5,
                 char param_6)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  int iVar4;
  code *pcVar5;
  undefined1 *puVar6;
  code *pcVar7;
  code *pcVar8;
  undefined1 local_100 [16];
  undefined1 local_f0 [16];
  undefined1 local_e0 [16];
  undefined1 local_d0 [16];
  undefined1 local_c0 [4];
  undefined1 local_bc [4];
  undefined1 local_b8 [4];
  undefined1 local_b4 [4];
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined1 local_a0 [4];
  undefined4 local_9c;
  int local_98;
  char *local_94;
  int local_90;
  undefined1 local_8c [4];
  undefined4 local_88;
  undefined4 local_84;
  int local_80;
  undefined1 local_7a;
  char local_79;
  int *local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ade0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcVar8 = FUN_004bc8c0;
  pcVar7 = FUN_0056f740;
  pcVar5 = FUN_00574a10;
  FUN_0081e820("CNetGameLobby::OnLobbyChatUpdate called for lobby ",param_1,", member ",param_2,
               ", changes ");
  uVar2 = FUN_0081e660();
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_0073ba70(uVar2);
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_0073ba70(uVar2);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  pbVar3 = std::basic_ostream<char,struct_std::c
```

## Short Conclusions

- The provided PDB does not match the GOG EXE by GUID, so it will not auto-apply cleanly in Ghidra.
- The PDB still comes from the same BattleZoneTest codebase family and exposes high-value names for lobby, map filter, map select, and user bar systems.
- The Ghidra decompilation aligns with those names at the feature level: the map filter path checks strings such as `All Maps`, `Strategy`, and `Death Match`; the user bar constructor creates `Whisper User` and `Mute User`; the slash command handler prints `/mute`, `/unmute`, `/kick`, `/lock`, and `/unlock`; and the lobby callback logs `CNetGameLobby::OnLobbyChatUpdate`.