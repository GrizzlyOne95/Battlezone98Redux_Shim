
void __fastcall FUN_00594950(int param_1)

{
  undefined4 uVar1;
  uint local_c;
  
  *(float *)(param_1 + 0x30) = (float)(DAT_02ce99b0 + DAT_02ce99b8) / 2.0;
  *(float *)(param_1 + 0x34) = (float)(DAT_02ce99b4 + DAT_02ce99bc) / 2.0;
  *(float *)(param_1 + 0x38) = (float)(DAT_02ce99b8 - DAT_02ce99b0);
  *(float *)(param_1 + 0x3c) = (float)(DAT_02ce99bc - DAT_02ce99b4);
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 1;
  *(undefined4 *)(param_1 + 0x74) = 0;
  FUN_005982c0();
  *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
  *(undefined **)(param_1 + 0x7c) = &DAT_009174c4;
  *(undefined4 *)(param_1 + 0xac) = 0;
  for (local_c = 0; local_c < 0xe; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0xf4 + local_c * 4) = DAT_00917570;
  }
  *(undefined4 *)(param_1 + 0xf4) = DAT_009175ac;
  *(undefined4 *)(param_1 + 0xf8) = DAT_00917588;
  *(undefined4 *)(param_1 + 0xfc) = 0xffcccc99;
  *(undefined4 *)(param_1 + 0x100) = DAT_0091757c;
  *(undefined4 *)(param_1 + 0x104) = DAT_00917558;
  *(undefined4 *)(param_1 + 0x108) = DAT_0091755c;
  *(undefined4 *)(param_1 + 0x10c) = DAT_00917560;
  *(undefined4 *)(param_1 + 0x114) = DAT_00917598;
  *(undefined4 *)(param_1 + 0x118) = 0xff66cc66;
  *(undefined4 *)(param_1 + 0x11c) = DAT_00917590;
  *(undefined4 *)(param_1 + 0x120) = 0xffcc6666;
  *(undefined4 *)(param_1 + 0x124) = DAT_0091759c;
  *(undefined4 *)(param_1 + 0x128) = 0xffb2b266;
  *(undefined4 *)(param_1 + 300) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x130) = DAT_009175b0;
  *(undefined4 *)(param_1 + 0x134) = DAT_00917590;
  *(undefined4 *)(param_1 + 0x138) = DAT_0091757c;
  *(undefined4 *)(param_1 + 0x13c) = DAT_00917578;
  *(undefined4 *)(param_1 + 0x140) = DAT_0091755c;
  *(undefined4 *)(param_1 + 0x144) = DAT_00917598;
  *(undefined4 *)(param_1 + 0x148) = DAT_00917558;
  *(undefined4 *)(param_1 + 0x14c) = DAT_0091755c;
  *(undefined4 *)(param_1 + 0x150) = DAT_00917584;
  *(undefined4 *)(param_1 + 0x154) = DAT_00917570;
  uVar1 = FUN_0068bed0("key_0");
  *(undefined4 *)(param_1 + 0x158) = uVar1;
  uVar1 = FUN_0068bed0("key_TAB");
  *(undefined4 *)(param_1 + 0x15c) = uVar1;
  return;
}

