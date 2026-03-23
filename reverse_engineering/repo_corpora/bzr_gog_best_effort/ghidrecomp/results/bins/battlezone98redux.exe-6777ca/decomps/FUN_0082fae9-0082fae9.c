
void FUN_0082fae9(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_2 + 0x10);
  if (*(int **)(param_2 + 8) != piVar1) {
    *(int *)(*(int *)(param_2 + 0x14) + 0x10) = *piVar1;
    *(undefined4 *)(*piVar1 + 0x14) = *(undefined4 *)(param_2 + 0x14);
  }
  FUN_00838869(param_1,param_2,0x20,0);
  return;
}

