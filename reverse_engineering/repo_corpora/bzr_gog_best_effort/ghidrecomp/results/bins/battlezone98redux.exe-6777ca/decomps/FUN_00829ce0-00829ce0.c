
QuickBitSet * __fastcall FUN_00829ce0(QuickBitSet *param_1)

{
  undefined4 uVar1;
  
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  uVar1 = FUN_00829e10();
  *(undefined4 *)param_1 = uVar1;
  return param_1;
}

