
void FUN_00831c7a(int param_1,int param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  param_2 = param_2 - *(int *)(param_1 + 0x20);
  *puVar1 = *param_3;
  puVar1[1] = param_3[1];
  puVar1[2] = param_3[2];
  iVar2 = *(int *)(param_1 + 8);
  *(undefined4 *)(iVar2 + 0x10) = *param_4;
  *(undefined4 *)(iVar2 + 0x14) = param_4[1];
  *(undefined4 *)(iVar2 + 0x18) = param_4[2];
  iVar2 = *(int *)(param_1 + 8);
  *(undefined4 *)(iVar2 + 0x20) = *param_5;
  *(undefined4 *)(iVar2 + 0x24) = param_5[1];
  *(undefined4 *)(iVar2 + 0x28) = param_5[2];
  if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x31) {
    FUN_0082f194(param_1,3);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x30;
  FUN_0082f062(param_1,*(int *)(param_1 + 8) + -0x30,1);
  iVar2 = *(int *)(param_1 + 0x20);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  puVar1 = *(undefined4 **)(param_1 + 8);
  *(undefined4 *)(iVar2 + param_2) = *puVar1;
  *(undefined4 *)(iVar2 + 4 + param_2) = puVar1[1];
  *(undefined4 *)(iVar2 + 8 + param_2) = puVar1[2];
  return;
}

