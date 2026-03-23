
void FUN_0082eef5(int param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x68);
  *(uint *)(param_1 + 8) =
       (*(int *)(param_1 + 8) - param_2 & 0xfffffff0U) + *(int *)(param_1 + 0x20);
  for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    puVar1[2] = (puVar1[2] - param_2 & 0xfffffff0U) + *(int *)(param_1 + 0x20);
  }
  for (piVar2 = *(int **)(param_1 + 0x28); piVar2 <= *(int **)(param_1 + 0x14); piVar2 = piVar2 + 6)
  {
    piVar2[2] = (piVar2[2] - param_2 & 0xfffffff0U) + *(int *)(param_1 + 0x20);
    *piVar2 = (*piVar2 - param_2 & 0xfffffff0U) + *(int *)(param_1 + 0x20);
    piVar2[1] = (piVar2[1] - param_2 & 0xfffffff0U) + *(int *)(param_1 + 0x20);
  }
  *(uint *)(param_1 + 0xc) =
       (*(int *)(param_1 + 0xc) - param_2 & 0xfffffff0U) + *(int *)(param_1 + 0x20);
  return;
}

