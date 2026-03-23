
QuickBitSet * __fastcall FUN_006d7820(QuickBitSet *param_1)

{
  undefined4 uVar1;
  
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  uVar1 = FUN_006d8160();
  *(undefined4 *)param_1 = uVar1;
  return param_1;
}

