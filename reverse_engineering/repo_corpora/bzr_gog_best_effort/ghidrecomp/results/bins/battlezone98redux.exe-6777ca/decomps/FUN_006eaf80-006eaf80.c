
QuickBitSet * __fastcall FUN_006eaf80(QuickBitSet *param_1)

{
  undefined4 uVar1;
  undefined1 local_10 [8];
  QuickBitSet *local_8;
  
  local_8 = param_1;
  Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  uVar1 = begin(local_10);
  _Reset<>(uVar1);
  FUN_006ca8c0();
  return local_8;
}

