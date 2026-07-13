
void FUN_0082d86b(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00838869(param_2,0,0,0xc0);
  *(int *)(param_1 + 0x28) = iVar1;
  *(int *)(param_1 + 0x14) = iVar1;
  *(undefined4 *)(param_1 + 0x30) = 8;
  *(int *)(param_1 + 0x24) = iVar1 + 0xa8;
  iVar1 = FUN_00838869(param_2,0,0,0x2d0);
  *(int *)(param_1 + 8) = iVar1;
  *(int *)(param_1 + 0x20) = iVar1;
  *(undefined4 *)(param_1 + 0x2c) = 0x2d;
  *(int *)(param_1 + 0x1c) = iVar1 + 0x270;
  *(int *)(*(int *)(param_1 + 0x14) + 4) = iVar1;
  *(undefined4 *)(*(int *)(param_1 + 8) + 8) = 0;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  **(undefined4 **)(param_1 + 0x14) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(param_1 + 0xc) = **(undefined4 **)(param_1 + 0x14);
  (*(undefined4 **)(param_1 + 0x14))[2] = *(int *)(param_1 + 8) + 0x140;
  return;
}

