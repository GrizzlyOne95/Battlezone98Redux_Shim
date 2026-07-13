
undefined4 * FUN_006d1850(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  cVar1 = FUN_0042d8f0();
  if (cVar1 == '\0') {
    FUN_00438b60(param_3);
    <>(param_3);
    puVar2 = (undefined4 *)FUN_0042d8c0(local_18);
    local_10 = *puVar2;
    local_14 = param_2;
    FUN_006d5150(param_2,local_8 + 0xc,local_10);
    puVar2 = (undefined4 *)FUN_0044f170();
    *param_1 = *puVar2;
  }
  else {
    local_c = param_2;
    FUN_006d5070(param_1,param_2,param_3);
  }
  return param_1;
}

