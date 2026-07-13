
void __thiscall FUN_004d2840(int param_1,undefined4 param_2)

{
  float *pfVar1;
  int iVar2;
  undefined1 local_64 [12];
  undefined4 local_58;
  int local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_54 = param_1;
  if (0 < *(int *)(*(int *)(param_1 + 0xc) + 0x80)) {
    pfVar1 = (float *)FUN_006897e0(local_64,param_2,*(undefined8 *)(*(int *)(param_1 + 0x14) + 0x48)
                                   ,*(undefined8 *)(*(int *)(param_1 + 0x14) + 0x50),
                                   *(undefined8 *)(*(int *)(param_1 + 0x14) + 0x58));
    local_50 = *pfVar1;
    local_4c = pfVar1[1];
    local_48 = pfVar1[2];
    local_44 = local_50;
    local_40 = local_4c;
    local_3c = local_48;
    iVar2 = FUN_006895d0();
    if (iVar2 < 1) {
      local_38 = local_44 - *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_34 = local_40 + *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_30 = local_3c;
      local_2c = local_44 + *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_28 = local_40 + *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_24 = local_3c;
      local_20 = local_44 + *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_1c = local_40 - *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_18 = local_3c;
      local_14 = local_44 - *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_10 = local_40 - *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      local_c = local_3c;
      local_58 = DAT_00920ef4;
      DAT_00920ef4 = local_3c - *(float *)(*(int *)(local_54 + 0x14) + 0xac);
      FUN_0068d2f0(param_2,*(undefined4 *)(local_54 + 0xe8),&local_38,4);
      DAT_00920ef4 = (float)local_58;
    }
  }
  FUN_0083e885();
  return;
}

