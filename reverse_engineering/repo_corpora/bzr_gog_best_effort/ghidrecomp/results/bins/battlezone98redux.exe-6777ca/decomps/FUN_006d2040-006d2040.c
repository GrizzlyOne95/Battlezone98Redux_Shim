
undefined4 * FUN_006d2040(undefined4 param_1,COleCurrency *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  undefined1 *puVar7;
  undefined1 local_1c [8];
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [4];
  undefined4 *local_8;
  
  FUN_006c9a90(1,0);
  cVar1 = FUN_006ce2d0();
  if (((cVar1 == '\0') && (cVar1 = FUN_006ce2b0(), cVar1 == '\0')) &&
     (cVar1 = FUN_006d1fe0(), cVar1 == '\0')) {
    uVar2 = get();
    uVar4 = FUN_006d21b0();
    lVar5 = __allmul(uVar2,0,uVar4);
    lVar6 = FUN_006ce370();
    FUN_006c9a90(lVar5 + lVar6);
    *local_8 = local_14;
    local_8[1] = local_10;
    return local_8;
  }
  uVar2 = FUN_006d54c0(local_c);
  puVar7 = local_1c;
  COleCurrency::operator_union_tagCY(param_2);
  puVar3 = (undefined4 *)FUN_006de060(puVar7,uVar2);
  uVar2 = puVar3[1];
  *local_8 = *puVar3;
  local_8[1] = uVar2;
  return local_8;
}

