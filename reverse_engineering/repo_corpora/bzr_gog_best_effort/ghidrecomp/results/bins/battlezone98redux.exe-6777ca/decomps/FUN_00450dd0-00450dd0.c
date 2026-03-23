
void __thiscall FUN_00450dd0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 local_90 [8];
  undefined1 local_88 [8];
  int local_80;
  int local_7c;
  undefined4 *local_78;
  int local_74;
  void *local_70;
  int local_6c;
  undefined4 *local_68;
  void *local_64;
  undefined4 local_60;
  undefined4 *local_58;
  char local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846a30;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ParticleSimulateClass::vftable;
  local_58 = param_1;
  FUN_0044ea00(local_14);
  FUN_0044e900();
  FUN_00588c30(param_3,local_58 + 5,local_58 + 0x15,0x40,0x40);
  sprintf(local_54,"%.*s.odf",0x3b,local_58 + 5);
  *(undefined1 *)(local_58 + 0x40) = DAT_0091553d;
  uVar1 = FUN_00446460(param_3,0x811c9dc5);
  local_58[0x35] = uVar1;
  if (param_2 == (undefined4 *)0x0) {
    local_68 = local_58;
  }
  else {
    local_68 = param_2;
  }
  local_58[0x36] = local_68;
  if (DAT_00915660 == 0) {
    local_70 = operator_new(0x20);
    local_8 = 0;
    if (local_70 == (void *)0x0) {
      local_74 = 0;
    }
    else {
      local_74 = FUN_0044ea40();
    }
    local_7c = local_74;
    local_8 = 0xffffffff;
    DAT_00915660 = local_74;
  }
  local_78 = local_58;
  uVar1 = make_pair<>(local_88,local_58 + 0x35,&local_78);
  FUN_0044fad0(local_90,uVar1);
  if (DAT_0091565c == 0) {
    local_64 = operator_new(0x14);
    local_8 = 1;
    if (local_64 == (void *)0x0) {
      local_6c = 0;
    }
    else {
      local_6c = FUN_0044e900();
    }
    local_80 = local_6c;
    local_8 = 0xffffffff;
    DAT_0091565c = local_6c;
  }
  if (param_2 == (undefined4 *)0x0) {
    local_58[0x38] = 0x3f800000;
    local_58[0x39] = 0;
    local_58[0x3a] = 0x40;
  }
  else {
    uVar1 = FUN_0044e4c0(param_3);
    local_58[0x37] = uVar1;
    local_60 = FUN_00446460(local_58 + 0x15,0x811c9dc5);
    FUN_00589430(local_54);
    local_8 = 2;
    FUN_00589800(local_60,0x5212abee,local_58 + 0x38,param_2[0x38]);
    FUN_00589800(local_60,0x826cd95e,local_58 + 0x39,param_2[0x39]);
    FUN_00589760(local_60,0xe09fa060,local_58 + 0x3a,param_2[0x3a]);
    local_8 = 0xffffffff;
    FUN_00589530();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

