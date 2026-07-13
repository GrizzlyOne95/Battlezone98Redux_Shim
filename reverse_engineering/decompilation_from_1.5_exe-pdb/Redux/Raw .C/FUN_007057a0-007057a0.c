
undefined4 * FUN_007057a0(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  int local_8;
  
  FUN_00421ec0();
  local_10 = FUN_006cc070();
  cVar1 = FUN_0044bb90();
  if (cVar1 != '\0') {
    FUN_00421ec0();
    cVar1 = FUN_00705180();
    if (cVar1 != '\0') {
      local_c = 0;
      local_b = 0;
      local_a = 0xff;
      local_9 = 0xff;
      FUN_006ab750();
      puVar2 = (undefined4 *)FUN_00707f30(local_20,&local_c,4,local_10);
      local_18 = *puVar2;
      local_14 = puVar2[1];
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        *param_1 = local_18;
        param_1[1] = local_14;
        return param_1;
      }
    }
  }
  iVar3 = FUN_006ba430(local_8 + 0xc);
  if ((iVar3 == 1) && (cVar1 = FUN_004c85a0(), cVar1 == '\0')) {
    make_error_code(param_1,0x10);
    return param_1;
  }
  *(undefined4 *)(local_8 + 0x5c) = 4;
  FUN_006ab750();
  return param_1;
}

