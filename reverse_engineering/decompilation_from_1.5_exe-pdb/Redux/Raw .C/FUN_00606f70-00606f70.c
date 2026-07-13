
void __thiscall FUN_00606f70(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_40 [12];
  float local_34;
  float local_30;
  undefined4 *local_2c;
  uint local_28;
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0x4c) = *param_2;
  *(undefined4 *)(param_1 + 0x50) = param_2[1];
  *(undefined4 *)(param_1 + 0x54) = param_2[2];
  local_2c = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_24 = param_1;
  fVar3 = (float10)FUN_00453f80(*local_2c);
  local_30 = (float)fVar3;
  if (local_30 == 1.0) {
    local_28 = 0x3e800000;
  }
  else {
    fVar3 = (float10)FUN_00453f80(*local_2c);
    local_34 = (float)fVar3;
    if (local_34 <= 0.7) {
      local_28 = 0x3f800000;
    }
    else {
      local_28 = 0x3f000000;
    }
  }
  uVar1 = FUN_0045c4d0();
  pfVar2 = (float *)FUN_00440300(local_40,local_24 + 0x4c,uVar1);
  local_20 = *pfVar2;
  local_1c = pfVar2[1];
  local_18 = pfVar2[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  fVar3 = (float10)FUN_00447ed0(local_18 * *(float *)(local_24 + 100),local_28 ^ 0x80000000,local_28
                               );
  local_2c[3] = (float)fVar3;
  fVar3 = (float10)FUN_00447ed0(local_20 * *(float *)(local_24 + 0x68),local_28 ^ 0x80000000,
                                local_28);
  local_2c[2] = (float)fVar3;
  local_2c[4] = 0;
  FUN_0083e885();
  return;
}

