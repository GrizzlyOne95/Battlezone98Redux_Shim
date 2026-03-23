
undefined4
FUN_00831d18(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  
  iVar1 = FUN_008334a2(param_1,param_2,param_5);
  if (*(int *)(iVar1 + 8) == 0) {
    iVar1 = FUN_008334a2(param_1,param_3,param_5);
    if (*(int *)(iVar1 + 8) == 0) {
      return 0;
    }
  }
  FUN_00831c7a(param_1,param_4,iVar1,param_2,param_3);
  return 1;
}

