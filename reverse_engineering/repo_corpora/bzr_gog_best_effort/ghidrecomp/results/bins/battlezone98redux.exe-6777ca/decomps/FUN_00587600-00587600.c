
void __fastcall FUN_00587600(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_24 [12];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0x40) = 0x40800000;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(float *)(param_1 + 0x44) = (DAT_0091738c + DAT_00917394) * 0.5;
  *(float *)(param_1 + 0x4c) = (DAT_00917390 + DAT_00917388) * 0.5;
  local_18 = param_1;
  fVar2 = (float10)FUN_007855e0((double)*(float *)(param_1 + 0x44),
                                (double)*(float *)(param_1 + 0x4c));
  *(float *)(local_18 + 0x48) = (float)fVar2;
  puVar1 = (undefined4 *)FUN_00440000(local_24,0,0,0x3f800000);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_18 + 0x50) = local_14;
  *(undefined4 *)(local_18 + 0x54) = local_10;
  *(undefined4 *)(local_18 + 0x58) = local_c;
  FUN_0083e885();
  return;
}

