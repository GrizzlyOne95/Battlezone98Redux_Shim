
void __fastcall FUN_0049b520(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  int local_10;
  int local_c;
  
  if ((DAT_008eaad8 != 9) && (DAT_008eaad8 != 10)) {
    fVar7 = (float10)FUN_00822d60();
    local_c = 0;
    local_10 = 0;
    if (0.0 < *(float *)(param_1 + 0x28)) {
      if (*(float *)(param_1 + 0x28) <= 1.0) {
        local_10 = (int)(*(float *)(param_1 + 0x28) * 224.0);
      }
      else {
        local_10 = 0xe0;
      }
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
    if (0.0 < *(float *)(param_1 + 0x2c)) {
      if (*(float *)(param_1 + 0x2c) <= 1.0) {
        local_c = (int)(*(float *)(param_1 + 0x2c) * 224.0);
      }
      else {
        local_c = 0xe0;
      }
      *(float *)(param_1 + 0x2c) =
           *(float *)(param_1 + 0x2c) -
           *(float *)(param_1 + 0x2c) * *(float *)(param_1 + 0x30) * (float)fVar7;
      if (*(float *)(param_1 + 0x2c) <= 0.01 && *(float *)(param_1 + 0x2c) != 0.01) {
        *(undefined4 *)(param_1 + 0x2c) = 0;
      }
    }
    fVar4 = DAT_00920ef4;
    iVar6 = (local_c + local_10) - (local_c * local_10) / 0xff;
    DAT_00920ef4 = fVar4;
    if (0 < iVar6) {
      bVar1 = *(byte *)(param_1 + 0x34);
      bVar2 = *(byte *)(param_1 + 0x35);
      bVar3 = *(byte *)(param_1 + 0x36);
      DAT_00920ef4 = DAT_00920ef4 - 0.001;
      iVar5 = FUN_00439e60();
      iVar5 = *(int *)(iVar5 + 0x38);
      FUN_0043fb00(iVar6 * 0x1000000 |
                   ((int)((uint)bVar1 * local_c + (0xff - local_c) * local_10) / iVar6 & 0xffU) <<
                   0x10 | ((int)((uint)bVar2 * local_c + (0xff - local_c) * local_10) / iVar6 &
                          0xffU) << 8 |
                   (int)((uint)bVar3 * local_c + (0xff - local_c) * local_10) / iVar6 & 0xffU,
                   *(undefined4 *)(iVar5 + 8),*(undefined4 *)(iVar5 + 0xc),
                   *(undefined4 *)(iVar5 + 0x10),*(undefined4 *)(iVar5 + 0x14));
      DAT_00920ef4 = fVar4;
    }
  }
  return;
}

