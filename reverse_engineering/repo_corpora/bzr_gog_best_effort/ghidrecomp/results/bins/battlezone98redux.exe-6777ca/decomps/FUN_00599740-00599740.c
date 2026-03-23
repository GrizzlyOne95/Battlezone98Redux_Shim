
void __fastcall FUN_00599740(int param_1)

{
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0xbf800000;
  DAT_02a13ccc = 0;
  DAT_02a13cd4 = *(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8);
  DAT_02a13cd0 = *(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc);
  *(undefined4 *)(param_1 + 0xe0) = 0;
  return;
}

