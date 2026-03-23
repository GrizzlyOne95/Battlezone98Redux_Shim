
undefined4 * FUN_006d9a90(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00423890();
  local_8 = param_2;
  do {
    local_c = local_8;
    puVar2 = (undefined4 *)FUN_006e7f90(local_10,local_8,param_3);
    local_8 = *puVar2;
    cVar1 = FID_conflict_operator__(&param_3);
    if (cVar1 == '\0') break;
    cVar1 = FID_conflict_operator__(&local_8);
  } while (cVar1 != '\0');
  *param_1 = local_8;
  return param_1;
}

