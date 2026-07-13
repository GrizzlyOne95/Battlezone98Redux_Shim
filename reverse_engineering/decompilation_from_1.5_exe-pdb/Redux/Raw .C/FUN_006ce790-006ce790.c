
undefined4 FUN_006ce790(undefined4 param_1,COleCurrency *param_2,COleCurrency *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined1 *puVar5;
  undefined1 local_1c [16];
  longlong local_c;
  
  cVar1 = FUN_006d21f0();
  if ((cVar1 == '\0') && (cVar1 = FUN_006d21f0(), cVar1 == '\0')) {
    lVar4 = FUN_006ce370();
    local_c = FUN_006ce370();
    local_c = lVar4 - local_c;
    FUN_006b28f0(0,0,0,local_c);
    return param_1;
  }
  uVar2 = COleCurrency::operator_union_tagCY(param_3);
  puVar5 = local_1c;
  COleCurrency::operator_union_tagCY(param_2);
  FUN_006dd310(puVar5,uVar2);
  uVar3 = FUN_006c94e0();
  uVar2 = FUN_006d1ad0(uVar3);
  FUN_006b2920(uVar2);
  return param_1;
}

