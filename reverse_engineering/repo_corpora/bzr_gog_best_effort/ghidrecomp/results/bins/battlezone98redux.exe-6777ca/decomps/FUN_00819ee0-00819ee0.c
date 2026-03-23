
QuickBitSet * __fastcall FUN_00819ee0(QuickBitSet *param_1)

{
  undefined4 uVar1;
  
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  uVar1 = FUN_00819f10();
  *(undefined4 *)param_1 = uVar1;
  return param_1;
}

