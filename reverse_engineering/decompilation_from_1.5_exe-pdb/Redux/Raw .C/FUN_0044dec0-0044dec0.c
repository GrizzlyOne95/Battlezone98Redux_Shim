
undefined4 * __thiscall FUN_0044dec0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  int local_3c;
  undefined4 *local_38;
  int local_34;
  int local_30;
  void *local_2c;
  int local_28;
  void *local_24;
  undefined4 *local_20;
  undefined4 local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846860;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ParticleRenderClass::vftable;
  local_14 = param_1;
  FUN_0044ea00(uVar1);
  FUN_0044e900();
  FUN_00588c30(param_3,local_14 + 5,local_14 + 0x15,0x40,0x40);
  sprintf((char *)(local_14 + 0x25),"%.*s.odf",0x3b,local_14 + 5);
  *(undefined1 *)(local_14 + 0x40) = DAT_0091552b;
  if (param_2 == (undefined4 *)0x0) {
    local_20 = local_14;
  }
  else {
    local_20 = param_2;
  }
  local_14[0x36] = local_20;
  uVar2 = FUN_00446460(param_3,0x811c9dc5);
  local_14[0x35] = uVar2;
  if (DAT_00915658 == 0) {
    local_24 = operator_new(0x20);
    local_8 = 0;
    if (local_24 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_0044ea40();
    }
    local_34 = local_28;
    local_8 = 0xffffffff;
    DAT_00915658 = local_28;
  }
  local_38 = local_14;
  uVar2 = make_pair<>(local_44,local_14 + 0x35,&local_38);
  FUN_0044fad0(local_4c,uVar2);
  if (DAT_00915654 == 0) {
    local_2c = operator_new(0x14);
    local_8 = 1;
    if (local_2c == (void *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = FUN_0044e900();
    }
    local_3c = local_30;
    local_8 = 0xffffffff;
    DAT_00915654 = local_30;
  }
  local_14[0x3c] = 0;
  if (param_2 == (undefined4 *)0x0) {
    local_14[0x3d] = 0;
    local_14[0x3e] = 2;
    local_14[0x3f] = 0;
  }
  else {
    local_1c = FUN_00446460(local_14 + 0x15,0x811c9dc5);
    FUN_00589430(local_14 + 0x25);
    local_8 = 2;
    FUN_005896c0(local_1c,0xc89676aa,local_14 + 0x3d,param_2[0x3d]);
    FUN_005896c0(local_1c,0x2d0b672c,local_14 + 0x3e,param_2[0x3e]);
    FUN_00589800(local_1c,0x826cd95e,local_14 + 0x3f,param_2[0x3f]);
    fVar3 = (float10)FUN_0044fb20(0,local_14[0x3f]);
    local_14[0x3f] = (float)fVar3;
    local_8 = 0xffffffff;
    FUN_00589530();
  }
  ExceptionList = local_10;
  return local_14;
}

