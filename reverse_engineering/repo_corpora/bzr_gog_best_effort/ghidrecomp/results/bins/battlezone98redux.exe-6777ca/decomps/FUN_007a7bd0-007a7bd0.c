
QuickBitSet * __fastcall FUN_007a7bd0(QuickBitSet *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  local_8 = 0;
  FUN_004bc320(0);
  *(undefined4 *)(param_1 + 8) = 0;
  ExceptionList = local_10;
  return param_1;
}

