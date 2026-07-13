
void FUN_0082d4cc(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = param_1;
  if ((param_1 != param_2) &&
     (*(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_3 * -0x10, 0 < param_3)) {
    param_1 = 0;
    do {
      puVar1 = *(undefined4 **)(param_2 + 8);
      puVar3 = (undefined4 *)(*(int *)(iVar2 + 8) + param_1);
      *(undefined4 **)(param_2 + 8) = puVar1 + 4;
      *puVar1 = *puVar3;
      puVar1[1] = puVar3[1];
      puVar1[2] = puVar3[2];
      param_1 = param_1 + 0x10;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

