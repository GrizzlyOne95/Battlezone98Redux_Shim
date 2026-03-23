
void FUN_00708260(int *param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_8 = *(int *)(param_3 + 4);
  if (local_8 == *param_1) {
    FUN_006d76c0(param_1,param_2);
    FUN_006d7700(param_1,param_2);
    FUN_006d76e0(param_1,param_2);
  }
  else if (*param_3 == '\0') {
    FUN_006d7700(&local_8,param_2);
    iVar1 = FUN_006d6730(param_1);
    if (local_8 == iVar1) {
      FUN_006d7700(param_1,param_2);
    }
  }
  else {
    FUN_006d76e0(&local_8,param_2);
    iVar1 = FUN_006d6720(param_1);
    if (local_8 == iVar1) {
      FUN_006d76e0(param_1,param_2);
    }
  }
  FUN_006d76c0(param_2,&local_8);
  local_c = 0;
  FUN_006d7700(param_2,&local_c);
  local_10 = 0;
  FUN_006d76e0(param_2,&local_10);
  return;
}

