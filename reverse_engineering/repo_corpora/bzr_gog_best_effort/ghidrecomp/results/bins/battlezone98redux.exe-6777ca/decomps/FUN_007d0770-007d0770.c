
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
  (**(code **)(*(int *)param_1[1] + 0x40))("MultiplayerModeButton_over.png");
  (**(code **)(*(int *)param_1[1] + 0x3c))("MultiplayerModeButton_on.png");
  uVar3 = FUN_0081cb40("first_letter",&DAT_0089ef88);
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_007d0700);
  FUN_007c23c0(FUN_007d0730);
  FUN_007d2110(param_1[1],0);
  if (param_8 == '\0') {
    pvVar2 = operator_new(0x1ec);
    local_8 = 2;
    if (pvVar2 == (void *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = FUN_007c2480("Kick User",param_3,param_4 + 96.0,0x42400000,0x42400000,0x20,param_2,
                              0,0);
    }
    local_8 = 0xffffffff;
    param_1[2] = local_30;
    FUN_007d2870("MultiplayerModeButton_off.png");
    (**(code **)(*(int *)param_1[2] + 0x40))("MultiplayerModeButton_over.png");
    (**(code **)(*(int *)param_1[2] + 0x3c))("MultiplayerModeButton_on.png");
    uVar3 = FUN_0081cb40("first_letter",&DAT_0089f02c);
    FUN_007c2950(uVar3);
    FUN_007c23e0(FUN_007d06f0);
    FUN_007c23c0(FUN_007d0750);
    FUN_007d2110(param_1[2],0);
  }
  else {
    param_1[2] = 0;
  }
  pvVar2 = operator_new(0x930);
  local_8 = 3;
  if (pvVar2 == (void *)0x0) {
    local_38 = 0;
  }
  else {
    local_38 = FUN_007cc390("Lobby",0x43870000,0x44750000,0x43a90000,0x422c0000,0x8020,param_2,0);
  }
  local_8 = 0xffffffff;
  param_1[6] = local_38;
  uVar3 = FUN_0081cb40("multi_help","whisper");
  (**(code **)(*(int *)param_1[6] + 0x3c))(uVar3);
  FUN_007cc5c0(0);
  FUN_007d2110(param_1[6],0);
  pvVar2 = operator_new(0x930);
  local_8 = 4;
  if (pvVar2 == (void *)0x0) {
    local_40 = 0;
  }
  else {
    local_40 = FUN_007cc390("Lobby",0x43870000,0x44750000,0x43a90000,0x422c0000,0x8020,param_2,0);
  }
  local_8 = 0xffffffff;
  param_1[7] = local_40;
  uVar3 = FUN_0081cb40("multi_help",&DAT_0089ef88);
  (**(code **)(*(int *)param_1[7] + 0x3c))(uVar3);
  FUN_007cc5c0(0);
  FUN_007d2110(param_1[7],0);
  pvVar2 = operator_new(0x930);
  local_8 = 5;
  if (pvVar2 == (void *)0x0) {
    local_48 = 0;
  }
  else {
    local_48 = FUN_007cc390("Lobby",0x43870000,0x44750000,0x43a90000,0x422c0000,0x8020,param_2,0);
  }
  local_8 = 0xffffffff;
  param_1[8] = local_48;
  uVar3 = FUN_0081cb40("multi_help",&DAT_0089f02c);
  (**(code **)(*(int *)param_1[8] + 0x3c))(uVar3);
  FUN_007cc5c0(0);
  FUN_007d2110(param_1[8],0);
  ExceptionList = local_10;
  return param_1;
}

