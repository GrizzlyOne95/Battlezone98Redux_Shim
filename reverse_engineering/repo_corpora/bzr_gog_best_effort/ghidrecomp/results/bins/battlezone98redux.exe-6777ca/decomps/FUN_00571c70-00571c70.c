
void __thiscall FUN_00571c70(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x410) = *param_2;
  *(undefined4 *)(param_1 + 0x414) = param_2[1];
  *(undefined4 *)(param_1 + 0x418) = param_2[2];
  if (*(int *)(param_1 + 8) == 3) {
    *(undefined4 *)(param_1 + 8) = 4;
  }
  *(undefined1 *)(param_1 + 0x41c) = 1;
  DAT_00917f50 = (uint)*(byte *)(param_2 + 3);
  iVar1 = FUN_005771b0(DAT_009180d4);
  if (iVar1 != 0) {
    FUN_00576370(0);
    FUN_00577900(*(undefined1 *)(param_2 + 3));
  }
  return;
}

