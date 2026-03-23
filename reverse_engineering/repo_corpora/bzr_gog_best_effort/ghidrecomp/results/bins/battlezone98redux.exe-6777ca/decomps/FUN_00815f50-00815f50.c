
int FUN_00815f50(int param_1)

{
  int iVar1;
  int local_c;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    local_c = FUN_006d6700(&param_1);
    iVar1 = FUN_006d6700(&local_c);
    if (param_1 == iVar1) break;
    local_8 = local_8 + 1;
    param_1 = local_c;
  }
  return local_8;
}

