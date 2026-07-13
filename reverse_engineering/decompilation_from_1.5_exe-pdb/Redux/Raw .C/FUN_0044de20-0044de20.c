
void __thiscall FUN_0044de20(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(int *)(param_1 + 0x68) != 0) {
    **(undefined4 **)(param_1 + 0x68) = 0;
  }
  *(undefined4 *)(param_1 + 0x68) = param_2;
  **(int **)(param_1 + 0x68) = param_1;
  if (param_3 == (undefined4 *)0x0) {
    *(undefined1 *)(param_1 + 0x1c) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x1c) = 1;
    puVar2 = (undefined4 *)(param_1 + 0x20);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_3;
      param_3 = param_3 + 1;
      puVar2 = puVar2 + 1;
    }
  }
  return;
}

