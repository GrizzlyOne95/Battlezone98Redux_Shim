
undefined4 * __thiscall FUN_00475510(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847588;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047e9c0(param_2,param_3);
  local_8 = 0;
  *param_1 = Artifact::vftable;
  param_1[6] = Artifact::vftable;
  uVar2 = FUN_0046cfe0(uVar1);
  param_1[0x88] = uVar2;
  ExceptionList = local_10;
  return param_1;
}

