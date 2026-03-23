
undefined4 FUN_006ce640(undefined4 param_1,COleCurrency *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  cVar1 = FUN_006d21f0();
  if (cVar1 == '\0') {
    uVar3 = FUN_006d2170();
    FUN_006b28f0(0,0,0,uVar3);
  }
  else {
    COleCurrency::operator_union_tagCY(param_2);
    uVar2 = FUN_006d1b40();
    FUN_006b2920(uVar2);
  }
  return param_1;
}

