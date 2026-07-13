
void __thiscall FUN_0041a750(int param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  int iVar2;
  float fVar3;
  
  FUN_00419b20(param_2,param_3);
  *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x28);
  iVar1 = FUN_004187d0();
  if (iVar1 != 0) {
    iVar2 = (*(int *)(param_1 + 0x24) - *(int *)(param_1 + 0x1c)) + 1;
    iVar1 = (int)((float)iVar2 * 0.5);
    *(int *)(param_1 + 0x1c) = (*(int *)(param_1 + 0x80) + iVar2 / 2) - iVar1 / 2;
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x1c) + -1 + iVar1;
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) - iVar1 / 2;
    *(int *)(param_1 + 0x34) = iVar1 / 2 + *(int *)(param_1 + 0x34);
  }
  iVar1 = FUN_004187d0();
  if (iVar1 != 0) {
    iVar1 = (*(int *)(param_1 + 0x28) - *(int *)(param_1 + 0x20)) + 1;
    fVar3 = (float)iVar1 * 0.5;
    *(int *)(param_1 + 0x20) =
         (int)(((float)*(int *)(param_1 + 0x84) + (float)iVar1 / 2.0) - fVar3 / 2.0);
    *(int *)(param_1 + 0x28) = (int)(((float)*(int *)(param_1 + 0x20) + fVar3) - 1.0);
    *(int *)(param_1 + 0x30) = (int)((float)*(int *)(param_1 + 0x30) - fVar3 / 2.0);
    *(int *)(param_1 + 0x38) = (int)((float)*(int *)(param_1 + 0x38) + fVar3 / 2.0);
  }
  FUN_00418a00(*(undefined4 *)(param_1 + 0x80),*(undefined4 *)(param_1 + 0x88));
  FUN_00418a00(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x8c));
  return;
}

