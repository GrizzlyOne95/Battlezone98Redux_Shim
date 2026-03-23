
QuickBitSet * __thiscall FUN_0066dee0(QuickBitSet *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084eb0b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  FUN_0066f170(param_2);
  local_8 = 0;
  uVar2 = FUN_0066e2a0(uVar1);
  *(undefined4 *)param_1 = uVar2;
  ExceptionList = local_10;
  return param_1;
}

