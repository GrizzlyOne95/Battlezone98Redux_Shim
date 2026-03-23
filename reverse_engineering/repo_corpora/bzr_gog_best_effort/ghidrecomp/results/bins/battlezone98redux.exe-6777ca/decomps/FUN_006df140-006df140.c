
undefined4 FUN_006df140(undefined4 param_1,COleCurrency *param_2,COleCurrency *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = COleCurrency::operator_union_tagCY(param_3);
  uVar2 = COleCurrency::operator_union_tagCY(param_2);
  FUN_006f0840(param_1,uVar2,uVar1);
  return param_1;
}

