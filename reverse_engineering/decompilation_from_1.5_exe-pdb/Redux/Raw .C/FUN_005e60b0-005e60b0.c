
void FUN_005e60b0(undefined4 param_1)

{
  double *pdVar1;
  undefined1 local_54 [24];
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00480470(param_1);
  pdVar1 = (double *)FUN_00447f60(local_54,*(int *)(local_3c + 0x14) + 0x20);
  local_38 = *(undefined4 *)pdVar1;
  uStack_34 = *(undefined4 *)((int)pdVar1 + 4);
  local_30 = *(undefined4 *)(pdVar1 + 1);
  uStack_2c = *(undefined4 *)((int)pdVar1 + 0xc);
  local_28 = *(undefined4 *)(pdVar1 + 2);
  uStack_24 = *(undefined4 *)((int)pdVar1 + 0x14);
  *(float *)(local_3c + 0x100) =
       (float)(*pdVar1 - *(double *)(local_3c + 0xe8)) *
       *(float *)(*(int *)(local_3c + 0x14) + 0x38) +
       (float)(pdVar1[1] - *(double *)(local_3c + 0xf0)) *
       *(float *)(*(int *)(local_3c + 0x14) + 0x3c) +
       (float)(pdVar1[2] - *(double *)(local_3c + 0xf8)) *
       *(float *)(*(int *)(local_3c + 0x14) + 0x40);
  local_20 = local_38;
  local_1c = uStack_34;
  local_18 = local_30;
  local_14 = uStack_2c;
  local_10 = local_28;
  local_c = uStack_24;
  FUN_0083e885();
  return;
}

