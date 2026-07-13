
undefined4 FUN_004e35a0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int local_8;
  
  iVar1 = FUN_004e3210(param_2,param_3);
  local_8 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0x68) <= local_8) {
      return 0;
    }
    piVar2 = (int *)(local_8 * 0x10 + *(int *)(param_1 + 0x74));
    if (*piVar2 == iVar1) break;
    local_8 = local_8 + 1;
  }
  *(int *)(param_1 + 100) = piVar2[1];
  return 1;
}

