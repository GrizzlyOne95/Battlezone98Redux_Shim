
void __thiscall FUN_005c1e70(int param_1,float param_2,float param_3)

{
  float *pfVar1;
  float10 fVar2;
  undefined1 local_38 [12];
  float local_2c;
  float local_28;
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  pfVar1 = (float *)FUN_004560b0(local_38,*(int *)(param_1 + 0xf4) + 0x20);
  local_20 = *pfVar1;
  local_1c = pfVar1[1];
  local_18 = pfVar1[2];
  local_2c = local_20 * param_2 + local_18 * param_3;
  local_28 = local_20 * param_3 - local_18 * param_2;
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  if (local_2c <= 0.0) {
    if (0.0 <= local_28) {
      *(undefined4 *)(*(int *)(local_24 + 0x230) + 0xc4) = 0x3f800000;
    }
    else {
      *(undefined4 *)(*(int *)(local_24 + 0x230) + 0xc4) = 0xbf800000;
    }
  }
  else {
    fVar2 = (float10)FUN_00447ed0(local_28 * 3.0 - *(float *)(local_24 + 0x13c) * 0.5,0xbf800000,
                                  0x3f800000);
    *(float *)(*(int *)(local_24 + 0x230) + 0xc4) = (float)fVar2;
  }
  FUN_0083e885();
  return;
}

