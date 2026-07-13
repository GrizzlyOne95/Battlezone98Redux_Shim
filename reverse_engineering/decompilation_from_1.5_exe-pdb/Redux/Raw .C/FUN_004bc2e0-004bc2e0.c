
QuickBitSet * __fastcall FUN_004bc2e0(QuickBitSet *param_1)

{
  undefined4 uVar1;
  
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  uVar1 = FUN_004bc340();
  *(undefined4 *)param_1 = uVar1;
  return param_1;
}

