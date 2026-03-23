
undefined4 FUN_006ce700(undefined4 param_1,COleCurrency *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  longlong lVar4;
  longlong lVar5;
  undefined1 *puVar6;
  undefined1 local_14 [16];
  
  cVar1 = FUN_006d21f0();
  if ((cVar1 == '\0') && (cVar1 = FUN_006d1fe0(), cVar1 == '\0')) {
    lVar4 = FUN_006ce370();
    lVar5 = FUN_006ce370();
    FUN_006b2940(lVar4 + lVar5);
    return param_1;
  }
  uVar2 = COleCurrency::operator_union_tagCY((COleCurrency *)&stack0x0000000c);
  puVar6 = local_14;
  COleCurrency::operator_union_tagCY(param_2);
  puVar3 = (undefined4 *)FUN_006dd1a0(puVar6,uVar2);
  FUN_006c9a90(*puVar3,puVar3[1]);
  return param_1;
}

