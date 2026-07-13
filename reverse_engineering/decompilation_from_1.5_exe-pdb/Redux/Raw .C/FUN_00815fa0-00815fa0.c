
int FUN_00815fa0(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  cVar1 = FUN_008160b0(param_1);
  if (cVar1 == '\0') {
    iVar3 = FUN_006d6720(param_1);
    if (iVar3 == 0) {
      local_c = *param_1;
      local_8 = FUN_006d6700(&local_c);
      while (iVar3 = FUN_006d6720(&local_8), local_c == iVar3) {
        local_c = local_8;
        local_8 = FUN_006d6700(&local_8);
      }
    }
    else {
      uVar2 = FUN_006d6720(param_1);
      local_8 = FUN_00816070(uVar2);
    }
  }
  else {
    uVar2 = FUN_006d6700(param_1);
    local_8 = FUN_00816070(uVar2);
  }
  return local_8;
}

