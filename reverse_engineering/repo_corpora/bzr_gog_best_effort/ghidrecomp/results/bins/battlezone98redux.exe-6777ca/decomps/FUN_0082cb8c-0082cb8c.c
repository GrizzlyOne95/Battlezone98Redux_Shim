
void FUN_0082cb8c(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int local_c;
  int local_8;
  
  if (param_4 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0082c4a6(param_1,param_4);
    iVar1 = iVar1 - *(int *)(param_1 + 0x20);
  }
  local_c = *(int *)(param_1 + 8) + (param_2 + 1) * -0x10;
  local_8 = param_3;
  FUN_0082f1b5(param_1,FUN_0082c471,&local_c,local_c - *(int *)(param_1 + 0x20),iVar1);
  if (param_3 == -1) {
    if (*(uint *)(*(int *)(param_1 + 0x14) + 8) <= *(uint *)(param_1 + 8)) {
      *(uint *)(*(int *)(param_1 + 0x14) + 8) = *(uint *)(param_1 + 8);
    }
  }
  return;
}

