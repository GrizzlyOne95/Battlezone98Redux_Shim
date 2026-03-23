
int FUN_006d4970(int *param_1)

{
  int iVar1;
  int local_c;
  int local_8;
  
  iVar1 = FUN_006d6730(param_1);
  if (iVar1 == 0) {
    local_c = *param_1;
    local_8 = FUN_006d6700(&local_c);
    while (iVar1 = FUN_006d6730(&local_8), local_c == iVar1) {
      local_c = local_8;
      local_8 = FUN_006d6700(&local_8);
    }
    iVar1 = FUN_006d6730(&local_c);
    if (iVar1 != local_8) {
      local_c = local_8;
    }
  }
  else {
    local_c = FUN_006d66c0(iVar1);
  }
  return local_c;
}

