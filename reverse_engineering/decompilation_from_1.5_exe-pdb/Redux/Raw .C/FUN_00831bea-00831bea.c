
void FUN_00831bea(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  *puVar1 = *param_2;
  puVar1[1] = param_2[1];
  puVar1[2] = param_2[2];
  iVar2 = *(int *)(param_1 + 8);
  *(undefined4 *)(iVar2 + 0x10) = *param_3;
  *(undefined4 *)(iVar2 + 0x14) = param_3[1];
  *(undefined4 *)(iVar2 + 0x18) = param_3[2];
  iVar2 = *(int *)(param_1 + 8);
  *(undefined4 *)(iVar2 + 0x20) = *param_4;
  *(undefined4 *)(iVar2 + 0x24) = param_4[1];
  *(undefined4 *)(iVar2 + 0x28) = param_4[2];
  iVar2 = *(int *)(param_1 + 8);
  *(undefined4 *)(iVar2 + 0x30) = *param_5;
  *(undefined4 *)(iVar2 + 0x34) = param_5[1];
  *(undefined4 *)(iVar2 + 0x38) = param_5[2];
  if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x41) {
    FUN_0082f194(param_1,4);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x40;
  FUN_0082f062(param_1,*(int *)(param_1 + 8) + -0x40,0);
  return;
}

