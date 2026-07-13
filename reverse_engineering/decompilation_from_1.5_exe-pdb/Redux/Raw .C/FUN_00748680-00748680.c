
QuickBitSet * __fastcall FUN_00748680(QuickBitSet *param_1)

{
  undefined4 uVar1;
  
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  uVar1 = FUN_007486d0();
  *(undefined4 *)param_1 = uVar1;
  return param_1;
}

