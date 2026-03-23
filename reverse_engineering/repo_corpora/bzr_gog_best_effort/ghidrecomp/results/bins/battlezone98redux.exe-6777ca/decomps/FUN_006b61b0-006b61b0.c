
undefined2 FUN_006b61b0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  char *_Str;
  undefined1 local_28 [8];
  undefined1 local_20 [16];
  int local_10;
  uint local_c;
  undefined2 local_6;
  
  puVar3 = (undefined4 *)FUN_006ab750();
  uVar1 = puVar3[1];
  *param_2 = *puVar3;
  param_2[1] = uVar1;
  cVar2 = FUN_0041f890();
  if (cVar2 == '\0') {
    _Str = (char *)FUN_0041f870();
    local_c = atoi(_Str);
    if (0xffff < local_c) {
      puVar3 = (undefined4 *)make_error_code(local_20,0x18);
      uVar1 = puVar3[1];
      *param_2 = *puVar3;
      param_2[1] = uVar1;
    }
    if (local_c == 0) {
      puVar3 = (undefined4 *)make_error_code(local_28,0x18);
      uVar1 = puVar3[1];
      *param_2 = *puVar3;
      param_2[1] = uVar1;
    }
  }
  else if (*(char *)(local_10 + 0x4a) == '\0') {
    local_6 = 0x50;
    local_c._0_2_ = local_6;
  }
  else {
    local_6 = 0x1bb;
    local_c._0_2_ = local_6;
  }
  return (undefined2)local_c;
}

