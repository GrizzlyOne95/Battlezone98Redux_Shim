
QuickBitSet * FUN_006ae3b0(QuickBitSet *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_006ae390(param_2);
  if (uVar1 < param_3) {
    Concurrency::details::QuickBitSet::QuickBitSet(param_1);
  }
  else {
    iVar2 = FUN_006d8ca0(param_2);
    iVar2 = iVar2 + param_3;
    iVar3 = FUN_006ae390(param_2,iVar2);
    FUN_00416430(iVar2,iVar3 - param_3);
  }
  return param_1;
}

