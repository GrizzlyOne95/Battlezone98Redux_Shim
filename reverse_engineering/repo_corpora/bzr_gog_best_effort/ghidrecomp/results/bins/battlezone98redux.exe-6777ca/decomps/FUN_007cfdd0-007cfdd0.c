
undefined4 * __thiscall
FUN_007cfdd0(undefined4 *param_1,undefined4 param_2,float param_3,float param_4,float param_5,
            float param_6,undefined4 param_7,undefined4 param_8)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_24;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862954;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  local_8 = 0;
  *param_1 = cUI_TextPopup::vftable;
  FUN_007d3f20(4);
  fVar4 = param_6 * 0.3333;
  param_5 = param_5 / 2.0;
  FUN_007d2870("POPUP224.png");
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_24 = 0;
  }
  else {
    local_24 = FUN_007c2480("LeftAlertButton",param_3,(param_4 + param_6) - fVar4,param_5,fVar4,0x20
                            ,param_8,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_24;
  FUN_007d3f20(6);
  FUN_007d2870("cancelon.png");
  uVar2 = FUN_0081cb40("multi_popup","cancel_button");
  FUN_007c2950(uVar2);
  (**(code **)(*(int *)param_1[0x51] + 0x40))("cancelon2.png");
  (**(code **)(*(int *)param_1[0x51] + 0x3c))("cancelcl.png");
  FUN_007d2110(param_1[0x51],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_2c = 0;
  }
  else {
    local_2c = FUN_007c2480("RightAlertButton",param_3 + param_5,(param_4 + param_6) - fVar4,param_5
                            ,fVar4,0x22,param_8,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_2c;
  FUN_007d3f20(6);
  FUN_007d2870("cancelon.png");
  uVar2 = FUN_0081cb40("multi_popup","ok_button");
  FUN_007c2950(uVar2);
  (**(code **)(*(int *)param_1[0x52] + 0x40))("cancelon2.png");
  (**(code **)(*(int *)param_1[0x52] + 0x3c))("cancelcl.png");
  FUN_007d2110(param_1[0x52],0);
  FUN_0081cb40("multi_common",&DAT_008714b0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_34 = 0;
  }
  else {
    local_34 = FUN_007cc390("PopupLabel",param_3 + 25.0,param_4 + 10.0,0x43160000,0x42340000,0x8020,
                            param_8,0);
  }
  local_8._0_1_ = 0;
  param_1[0x53] = local_34;
  FUN_007d3f20(5);
  (**(code **)(*(int *)param_1[0x53] + 0x3c))(&DAT_008a1ad8);
  FUN_007d2110(param_1[0x53],0);
  pvVar1 = operator_new(0x968);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_007cf410(1,0,0xf,"PopupEntry",param_3 + param_5 + 25.0,param_4 + 10.0,0x43160000,
                            0x42340000,0x8020,param_8);
  }
  local_8._0_1_ = 0;
  param_1[0x54] = local_3c;
  FUN_007d3f20(5);
  FUN_007d2110(param_1[0x54],0);
  uVar2 = FUN_0081cb40("option_box","Public");
  uVar3 = FUN_0081cb40("option_box","Private");
  pvVar1 = operator_new(500);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_44 = 0;
  }
  else {
    local_44 = FUN_007c3150("typecheckbox",0x42480000,fVar4 + 20.0,0x43010000,0x421c0000,0,param_1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x55] = local_44;
  FUN_007c3ac0(uVar2,0);
  FUN_007c3ac0(uVar3,1);
  FUN_007c3cf0(FUN_007cfdc0);
  FUN_007c3c10(0);
  FUN_007d2110(param_1[0x55],0);
  ExceptionList = local_10;
  return param_1;
}

