
int * FUN_004a84b0(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = (int *)FUN_004e0f70(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  piVar1 = (int *)(**(code **)(*piVar1 + 4))(param_1);
  *(int **)(piVar1[0x8c] + 0x120) = piVar1;
  uVar2 = FUN_0047e9a0(param_1);
  (**(code **)(*piVar1 + 4))(uVar2);
  return piVar1;
}

