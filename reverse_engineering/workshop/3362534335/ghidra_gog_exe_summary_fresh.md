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

### Map list fix support 1/3

- Address: `0x007A3110`
- Signature: `void FUN_007a3110(void);`
- PDB hints:
  - `UI_Multiplayer_Create.obj`
```c
void FUN_007a3110(void)

{
  FUN_007cb500();
  FUN_007a4260();
  return;
}
```

### Map list fix support 2/3 (HopFix3 step)

- Address: `0x007A3130`
- Signature: `void FUN_007a3130(void);`
- PDB hints:
  - `UI_Multiplayer_Create.obj`
```c
void FUN_007a3130(void)

{
  FUN_007cb540();
  FUN_007a4260();
  return;
}
```

### Map list fix support 3/3

- Address: `0x007A3D20`
- Signature: `void __thiscall FUN_007a3d20(int param_1,char param_2);`
- PDB hints:
  - `UI_Multiplayer_Create.obj`
```c
void __thiscall FUN_007a3d20(int param_1,char param_2)

{
  FUN_007cc5c0(param_2 == '\0');
  (**(code **)(**(int **)(param_1 + 0x2c) + 0x24))(param_2);
  FUN_007a4260();
  return;
}
```

### Map list coloring

- Address: `0x007A4400`
- Signature: `void __fastcall FUN_007a4400(undefined4 param_1);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
```c
void __fastcall FUN_007a4400(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = FUN_004170c0(param_1);
    if (uVar1 <= local_8) break;
    uVar3 = 0;
    uVar1 = local_8;
    FUN_00752d30(local_8);
    uVar2 = FUN_0041f870(uVar1,uVar3);
    FUN_007cabf0(uVar2,uVar1,uVar3);
    local_8 = local_8 + 1;
  }
  return;
}
```

### Map list filter scrolling

- Address: `0x00799770`
- Signature: `undefined4 FUN_00799770(undefined4 param_1);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
```c
undefined4 FUN_00799770(undefined4 param_1)

{
  FUN_007a3bd0(param_1);
  return 1;
}
```

### Map filter support (3/8)

- Address: `0x0079D6B0`
- Signature: `void FUN_0079d6b0(void);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
  - `filters.obj`
```c
void FUN_0079d6b0(void)

{
  FUN_0079e4f0();
  return;
}
```

### Map filter support (4/8)

- Address: `0x0079D690`
- Signature: `void FUN_0079d690(void);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
  - `filters.obj`
```c
void FUN_0079d690(void)

{
  FUN_0079de20();
  return;
}
```

### Vehicle list mod fix 1/4

- Address: `0x00766900`
- Signature: `void FUN_00766900(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>*param_1);`
- PDB hints:
  - `UI_Multiplayer_Create.obj`
```c
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00766900(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int aiStackY_108 [3];
  uint local_f8;
  int local_f4;
  int local_f0;
  undefined4 local_ec;
  undefined1 *local_e8;
  int local_e4;
  int local_e0;
  char *local_dc;
  int local_d8;
  char *local_d4;
  int local_d0;
  undefined1 *local_cc;
  int local_c8;
  uint local_c4;
  undefined1 *local_c0;
  uint local_bc;
  char *local_b8;
  char *local_b4;
  char local_ad;
  int local_ac;
  int local_a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d24b;
  local_10 = ExceptionList;
  local_f8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  aiStackY_108[2] = 0x76693d;
  local_14 = local_f8;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_1);
  local_8 =
```

### Vehicle list mod fix 2/4

- Address: `0x00799D70`
- Signature: `void FUN_00799d70(void);`
- PDB hints:
  - `UI_Multiplayer_Create.obj`
```c
/* WARNING: Removing unreachable block (ram,0x0079a4a1) */
/* WARNING: Removing unreachable block (ram,0x0079b5c0) */

void FUN_00799d70(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar7;
  undefined4 *puVar8;
  undefined1 auStack_440 [140];
  undefined4 uStack_3b4;
  uint uStack_3b0;
  char *pcStack_3a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_3a4;
  code *pcVar9;
  undefined1 auStack_378 [208];
  undefined1 *local_2a8;
  undefined1 *local_2a4;
  undefined4 local_2a0;
  undefined1 *local_298;
  undefined1 *local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined1 *local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined1 *local_274;
  undefined4 local_26c;
  undefined1 *local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  uint local_254;
  undefined4 local_250;
  uint local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  int local_234;
  int local_230;
  int local_22c;
  int local_228;
  char *local_224;
  int local_220;
  int *local_21c;
  undefined1 *local_218;
  undefined4 local_214;
  undefined1 local_20d;
  int local_20c;
  undefined4 local_208;
  undefined4 local_204;
  char *local_200;
  int local_1fc;
  int local_1f8;
  int local_1f4;
  uint local_1f0;
  int local_1ec;
  int local_1e8;
  int local_1e4;
  int local_1e0;
  int local_1dc;
  byte local_1d6;
  char local_1d5;
  int local_1d4;
  int local_1d0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_16c [24];
```

### BZRNET integration host

- Address: `0x007436C0`
- Signature: `void FUN_007436c0(undefined4 *param_1);`
- PDB hints:
  - `UI_MultiPlayer_Lobby.obj`
  - `lobby.obj`
```c
void FUN_007436c0(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  code *pcVar5;
  undefined1 auStack_330 [160];
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined *local_280;
  int local_27c;
  undefined1 *local_278;
  int local_274;
  int *local_270;
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
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b363;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_27c = FUN_007659f0(local_14);
  if (local_27c != 0) {
    FUN_0073bb30();
  }
  local_270[0xe] = 1;
  FUN_00741e80(local_ec,local_270 + 0x22);
  local_8 = 0;
  basic_string<>(&DAT_00879d2c);
  local_8._0_1_ = 1;
  (**(code **)(*local_270 + 0x20))(param_1,local_74,local_ec);
  local_8._0_1_ = 0;
  ~basic_string<>();
  if ((char)local_270[0x18] == '\0') {
    local_280 = &DAT_00873ef0;
  }
  else {
    local_280 = &DAT_00873c74;
  }
  basic_string<>(local_280);
  local_8._0_1_ = 2;
  basic_string<>("gameType");
  local_8._0_1_ = 3;
  (**(code **)(*local_270 + 0x20))(param_1,local_2c,local_44);
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  local_274 = FUN_007470b0(param_1,0);
  if (local_274 == 0) {
    local_28c = FUN_0073cc40();
    local_8._0_1_ = 4;
    local_288 = local_28c;
    FUN_00747db
```

### BZRNET integration client

- Address: `0x0073E240`
- Signature: `void __thiscall FUN_0073e240(int *param_1,char param_2,int *param_3,int param_4);`
- PDB hints:
  - `UI_MultiPlayer_Lobby.obj`
  - `lobby.obj`
```c
void __thiscall FUN_0073e240(int *param_1,char param_2,int *param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  code *pcVar6;
  undefined1 auStack_230 [176];
  undefined1 auStack_180 [160];
  undefined4 local_e0;
  undefined4 local_dc;
  int local_d8;
  undefined1 *local_d4;
  undefined1 *local_d0;
  int local_cc;
  int *local_c8;
  int local_c4;
  int *local_c0;
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
  puStack_c = &LAB_0085ad17;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_c0 = param_1;
  if (param_2 == '\0') {
    local_cc = param_4;
    if (param_4 == 0) {
      uVar2 = FUN_0081cb40("multi_error","kick_room");
      basic_string<>(uVar2);
      local_8 = 1;
      FUN_00745770(local_5c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else if (param_4 == 1) {
      uVar2 = FUN_0081cb40("multi_error","game_full");
      basic_string<>(uVar2);
      local_8 = 0;
      FUN_00745770(local_2c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else if (param_4 == 2) {
      uVar2 = FUN_0081cb40("multi_error","game_not_avail");
      basic_string<>(uVar2);
      local_8 = 2;
      FUN_00745770(local_8c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    pcVar6 = FUN_004bc8c0;
    pcVar5 = FUN_0056f740;
    FUN_0081e820("Failed to enter requested lobby:",p
```

### Ban button hook target

- Address: `0x007A4B60`
- Signature: `void FUN_007a4b60(void);`
- PDB hints:
  - `UI_UserBar.obj`
  - `lobby.obj`
```c
void FUN_007a4b60(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  float fVar11;
  code *pcVar12;
  float fVar13;
  code *pcVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  int *local_21c;
  undefined4 local_218;
  int *local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  float local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  int *local_1d0;
  void *local_1cc;
  void *local_1c8;
  int *local_1c4;
  undefined4 local_1c0;
  void *local_1bc;
  int *local_1b8;
  int *local_1b4;
  int *local_1b0;
  void *local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  void *local_19c;
  undefined4 local_198;
  undefined4 local_194;
  float local_190;
  void *local_18c;
  undefined4 local_188;
  void *local_184;
  undefined4 local_180;
  void *local_17c;
  int *local_178;
  int *local_174;
  void *local_170;
  void *local_16c;
  void *local_168;
  int *local_164;
  void *local_160;
  void *local_15c;
  void *local_158;
  undefined4 local_154;
  int *local_150;
  void *local_14c;
  uint local_148;
  undefined4 local_144;
  void *local_140;
  void *local_13c;
  void *local_138;
  u
```

### Map icon hook (map select)

- Address: `0x007A4260`
- Signature: `void FUN_007a4260(void);`
- PDB hints:
  - `UI_Multiplayer_MapSelect.obj`
```c
void FUN_007a4260(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint local_4c;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b7a8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  local_14 = uVar2;
  do {
    uVar3 = FUN_007cb5a0(uVar2);
    if (uVar3 <= local_4c) {
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    iVar4 = FUN_007c48b0();
    basic_string<>(&DAT_008a1ad8);
    local_8 = 0;
    uVar3 = FUN_004170c0();
    if (local_4c < uVar3) {
      iVar4 = FUN_00752d30(iVar4 + local_4c);
      uVar5 = FUN_007527e0(local_44,*(undefined1 *)(iVar4 + 0x38));
      FUN_0045e0f0(uVar5);
      ~basic_string<>();
    }
    cVar1 = FUN_007d3360();
    if (cVar1 == '\x01') {
      cVar1 = operator!=<>(local_2c,&DAT_008a1ad8);
      if (cVar1 == '\0') goto LAB_007a43a5;
      FUN_00764760();
      cVar1 = FUN_00742cf0();
      if (cVar1 != '\x01') goto LAB_007a43a5;
      puVar6 = (undefined4 *)FUN_004200d0(local_4c);
      (**(code **)(*(int *)*puVar6 + 0x24))(1);
      uVar5 = FUN_0041f870();
      FUN_004200d0(local_4c);
      FUN_007d2870(uVar5);
    }
    else {
LAB_007a43a5:
      puVar6 = (undefined4 *)FUN_004200d0(local_4c);
      (**(code **)(*(int *)*puVar6 + 0x24))(0);
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
    local_4c = local_4c + 1;
  } while( true );
}
```

### Map icon hook (lobby)

- Address: `0x007A1E20`
- Signature: `void __fastcall FUN_007a1e20(int param_1);`
- PDB hints:
  - `UI_MultiPlayer_Lobby.obj`
```c
void __fastcall FUN_007a1e20(int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_150 [8];
  undefined4 uStack_148;
  uint uStack_144;
  undefined1 *puStack_140;
  uint uStack_13c;
  undefined1 *puStack_138;
  uint uStack_134;
  undefined4 local_130;
  undefined1 *local_12c;
  undefined4 local_128;
  int *local_124;
  int *local_120;
  int *local_11c;
  int *local_118;
  int *local_114;
  int *local_110;
  int *local_10c;
  uint local_108;
  byte local_104;
  byte local_103;
  char local_102;
  char local_101;
  uint local_100;
  int local_fc;
  undefined1 local_f8 [56];
  byte local_c0;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008600c6;
  local_10 = ExceptionList;
  uStack_134 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_100 = 0;
  local_fc = param_1;
  local_14 = uStack_134;
  while( true ) {
    puStack_138 = (undefined1 *)0x7a1e7d;
    uVar1 = FUN_007cb5a0();
    if (uVar1 <= local_100) break;
    puStack_138 = (undefined1 *)0x7a1e9a;
    iVar2 = FUN_007c48b0();
    local_108 = iVar2 + local_100;
    puStack_138 = &DAT_008a1ad8;
    uStack_13c = 0x7a1eb3;
    basic_string<>();
    local_8 = 0;
    puStack_138 = (undefined1 *)0x7a1ecb;
    uVar1 = size();
    if (local_108 < uVar1) {
      puStack_138 = (undefined1 *)0x7a1ee2;
      FUN_00769eb0();
      local_8._0_1_ = 1;
      puStack_138 = local_f8;
      uStack_13c = local_108;
      puStack_140 = (undefined1 *)0x7a1f05;
      piVar3 = (int *)FUN_004200d0();
      local_12c = abStack_150;
      local_130 = std::basic_string<char,struct_std::char_traits<char>,clas
```

### Ogre resource loader

- Address: `0x00664110`
- Signature: `void FUN_00664110(void);`
- PDB hints:
  - `ogre`
  - `resource`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00664110(void)

{
  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  void *pvVar5;
  RenderSystem *pRVar6;
  undefined4 *puVar7;
  ExternalTextureSourceManager *this;
  ArchiveManager *this_00;
  _AFX_AYGSHELL_STATE *p_Var8;
  Manager *this_01;
  ResourceGroupManager *this_02;
  Root *this_03;
  uint uVar9;
  int iVar10;
  RenderWindow *pRVar11;
  SceneManager *pSVar12;
  Vector3 *pVVar13;
  TextureManager *this_04;
  HardwarePixelBuffer *pHVar14;
  int unaff_EBP;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar15;
  code *pcVar16;
  uint uVar17;
  PixelFormat PVar18;
  int iVar19;
  ManualResourceLoader *pMVar20;
  uint uVar21;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar22;
  bool bVar23;
  OgreTheoraVideoManager *pOVar24;
  ArchiveFactory *pAVar25;
  char *pcVar26;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar27;
  
  *(undefined4 *)(unaff_EBP + -4) = 9;
  basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 0xe;
  uVar4 = Ogre::ConfigFile::getSetting
                    ((ConfigFile *)(unaff_EBP + -0x530),
                     (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )(unaff_EBP + -0x434),
                     (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )(unaff_EBP + -0x2cc),
                     (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )&DAT_025f8dc8);
  *(undefined4 *)(unaff_EBP + -0x4fc) = uVar4;
  FUN_0045e0f0();
  ~basic_string<>();
  *(undefined1 *)(unaff_EB
```

### Lobby map name for unknown map

- Address: `0x007A11E0`
- Signature: `void FUN_007a11e0(void);`
- PDB hints:
  - `UI_MultiPlayer_Lobby.obj`
```c
void FUN_007a11e0(void)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  char *pcVar10;
  float10 fVar11;
  float10 fVar12;
  float fVar13;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_250 [8];
  undefined4 uStack_248;
  undefined1 *puStack_244;
  int local_180;
  int local_17c;
  float local_170;
  uint local_158;
  int local_150;
  undefined1 local_8c [96];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860071;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar3 = FUN_007cb0a0();
  FUN_0073a6b0();
  if (iVar3 != -1) {
    piVar4 = (int *)FUN_004200d0();
    iVar3 = *piVar4;
    FUN_00764760();
    FUN_0042d8c0();
    FUN_00764760();
    FID_conflict_begin();
    while (cVar2 = FUN_00420f10(), cVar2 != '\0') {
      iVar5 = FUN_0042de50();
      if (iVar5 == iVar3) {
        FUN_0042da60();
        break;
      }
      FUN_0042da80();
    }
  }
  iVar3 = FUN_007c48b0();
  iVar5 = FUN_007c48b0();
  FUN_007a10c0();
  FUN_00430590();
  FUN_0042d8c0();
  while( true ) {
    FID_conflict_begin();
    cVar2 = FUN_00420f10();
    if (cVar2 == '\0') break;
    iVar6 = FUN_0042de50();
    if (*(char *)(iVar6 + 0xb0) == '\x01') {
      FUN_0041ff90();
      FUN_0041f870();
      puStack_244 = (undefined1 *)0x7a142d;
      FUN_007cabf0();
      iVar6 = FUN_0056f900();
      if (iVar6 != 0) {
        FUN_0056f900();
        cVar2 = FUN_0056f780();
        if (cVar2 != '\0') {
          cVar2 = FUN_00742cf0();
          if
```

## Short Conclusions

- The provided PDB does not match the GOG EXE by GUID, so it will not auto-apply cleanly in Ghidra.
- The PDB still comes from the same BattleZoneTest codebase family and exposes high-value names for lobby, map filter, map select, and user bar systems.
- The Ghidra decompilation aligns with those names at the feature level: the map filter path checks strings such as `All Maps`, `Strategy`, and `Death Match`; the user bar constructor creates `Whisper User` and `Mute User`; the slash command handler prints `/mute`, `/unmute`, `/kick`, `/lock`, and `/unlock`; and the lobby callback logs `CNetGameLobby::OnLobbyChatUpdate`.