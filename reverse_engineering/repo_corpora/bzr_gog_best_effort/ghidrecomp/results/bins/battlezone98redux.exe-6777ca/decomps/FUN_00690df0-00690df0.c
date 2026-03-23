
void FUN_00690df0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x264);
  if (iVar1 != 0x28) {
    *(undefined4 *)(param_1 + 0x270 + iVar1 * 0x14) = param_2;
    *(undefined4 *)(param_1 + 0x274 + iVar1 * 0x14) = param_3;
    *(undefined4 *)(param_1 + 0x26c + iVar1 * 0x14) = param_4;
    *(undefined4 *)(param_1 + 0x278 + iVar1 * 0x14) = param_5;
    *(undefined4 *)(param_1 + 0x27c + iVar1 * 0x14) = param_6;
    *(int *)(param_1 + 0x264) = *(int *)(param_1 + 0x264) + 1;
  }
  return;
}

