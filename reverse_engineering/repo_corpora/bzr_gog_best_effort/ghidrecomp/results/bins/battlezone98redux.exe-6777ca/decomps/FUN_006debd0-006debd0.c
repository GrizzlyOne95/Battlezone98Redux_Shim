
undefined4 __thiscall FUN_006debd0(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00853ca8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = 0;
  local_8 = 0;
  FUN_006e2980(*param_1,param_1[1],&stack0x00000008);
  local_8 = 0xffffffff;
  FUN_006d4f70(uVar1,param_1,uVar2 | 1);
  ExceptionList = local_10;
  return param_2;
}

