
void FUN_006df180(COleCurrency *param_1,COleCurrency *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = COleCurrency::operator_union_tagCY(param_2);
  uVar2 = COleCurrency::operator_union_tagCY(param_1);
  FUN_006f0880(uVar2,uVar1);
  return;
}

