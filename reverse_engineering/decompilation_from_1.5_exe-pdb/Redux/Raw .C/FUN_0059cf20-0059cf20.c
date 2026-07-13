
undefined4 * __thiscall FUN_0059cf20(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c198;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004a7a20(param_2,param_3);
  local_8 = 0;
  *param_1 = Person::vftable;
  param_1[6] = Person::vftable;
  param_1[0x3b] = param_3;
  param_1[0x8d] = 2;
  param_1[0x8a] = 0;
  param_1[0xaa] = 2;
  FUN_0062a270(param_1[0x3d],param_1[0xaa],param_1 + 0xab,uVar1);
  param_1[0xad] = 0;
  uVar2 = FUN_0045c4f0(param_2);
  param_1[0x8c] = uVar2;
  *(undefined4 *)param_1[0x8c] = param_1[0x3c];
  *(undefined4 **)(param_1[0x8c] + 0x120) = param_1;
  ExceptionList = local_10;
  return param_1;
}

