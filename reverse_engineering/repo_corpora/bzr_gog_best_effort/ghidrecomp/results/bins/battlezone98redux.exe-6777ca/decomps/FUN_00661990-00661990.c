
undefined4 * __fastcall FUN_00661990(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084da36;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = EntityTransparencyMaterial::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 1));
  local_8 = 0;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 3));
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[5] = 0;
  FUN_004c85d0(uVar1);
  param_1[6] = 0;
  ExceptionList = local_10;
  return param_1;
}

