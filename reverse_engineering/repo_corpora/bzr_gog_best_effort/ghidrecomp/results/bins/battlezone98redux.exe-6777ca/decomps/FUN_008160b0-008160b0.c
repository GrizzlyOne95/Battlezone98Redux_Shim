
undefined4 FUN_008160b0(int *param_1)

{
  int iVar1;
  uint local_c;
  uint local_8;
  
  local_8 = FUN_006d6720(param_1);
  local_c = FUN_006d6730(param_1);
  iVar1 = FUN_006d6700(param_1);
  if ((iVar1 != 0) &&
     (((local_8 == 0 || (local_c == 0)) ||
      ((local_8 != local_c &&
       ((iVar1 = FUN_006d6700(&local_8), iVar1 == *param_1 &&
        (iVar1 = FUN_006d6700(&local_c), iVar1 == *param_1)))))))) {
    return 0;
  }
  return 1;
}

