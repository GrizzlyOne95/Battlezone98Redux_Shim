
void __thiscall FUN_0056a520(int *param_1,float param_2)

{
  float *pfVar1;
  float10 fVar2;
  undefined1 local_54 [12];
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  int local_30;
  float local_2c;
  float local_28;
  int *local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  if ((*(uint *)(param_1[5] + 0x14) & 8) != 0) {
    local_30 = (**(code **)(*param_1 + 0x24))();
    if (local_30 == 0) {
      local_24[0xf] = 0;
      local_24[0x10] = 0;
      local_24[0x11] = 0;
    }
    else {
      pfVar1 = (float *)(**(code **)(*(int *)(local_30 + 0x18) + 0xc))();
      local_14 = *pfVar1 - (float)*(double *)(local_24[5] + 0x48);
      local_10 = pfVar1[1] - (float)*(double *)(local_24[5] + 0x50);
      local_c = pfVar1[2] - (float)*(double *)(local_24[5] + 0x58);
      pfVar1 = (float *)FUN_004621a0(local_54,&local_14);
      local_20 = *pfVar1;
      local_1c = pfVar1[1];
      local_18 = pfVar1[2];
      local_3c = 1.0 / param_2;
      local_28 = (local_20 * *(float *)(local_24[5] + 0x20) +
                  local_1c * *(float *)(local_24[5] + 0x24) +
                 local_18 * *(float *)(local_24[5] + 0x28)) * local_3c;
      local_2c = (local_20 * *(float *)(local_24[5] + 0x2c) +
                  local_1c * *(float *)(local_24[5] + 0x30) +
                 local_18 * *(float *)(local_24[5] + 0x34)) * local_3c;
      local_38 = local_28 * local_28 + local_2c * local_2c;
      local_34 = *(float *)(local_24[3] + 0xd0);
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
      if (local_34 * local_34 < local_38) {
        fVar2 = (float10)FUN_00820570((double)local_38);
        local_48 = (float)fVar2;
        local_40 = local_48 * local_34;
        local_28 = local_28 * local_40;
        local_2c = local_2c * local_40;
        local_44 = local_48;
      }
      local_24[0xf] = (int)local_2c;
      local_24[0x10] = (int)-local_28;
      local_24[0x11] = 0;
    }
  }
  FUN_0083e885();
  return;
}

