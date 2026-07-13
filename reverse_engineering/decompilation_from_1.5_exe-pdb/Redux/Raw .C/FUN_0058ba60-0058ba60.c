
void __thiscall FUN_0058ba60(int param_1,undefined4 param_2)

{
  float *pfVar1;
  int iVar2;
  undefined1 local_6c [12];
  undefined4 local_60;
  undefined8 *local_5c;
  uint local_58;
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
  local_58 = *(uint *)(param_1 + 0x28);
  local_54 = param_1;
  while (local_58 != *(uint *)(local_54 + 0x2c)) {
    local_5c = (undefined8 *)(local_54 + 0x30 + local_58 * 0x30);
    local_58 = local_58 + 1;
    if (0xff < local_58) {
      local_58 = 0;
    }
    pfVar1 = (float *)FUN_006897e0(local_6c,param_2,*local_5c,local_5c[1],local_5c[2]);
    local_50 = *pfVar1;
    local_4c = pfVar1[1];
    local_48 = pfVar1[2];
    local_44 = local_50;
    local_40 = local_4c;
    local_3c = local_48;
    iVar2 = FUN_006895d0();
    if (iVar2 < 1) {
      local_38 = local_44 - *(float *)(local_54 + 0x3040);
      local_34 = local_40 + *(float *)(local_54 + 0x3040);
      local_30 = local_3c;
      local_2c = local_44 + *(float *)(local_54 + 0x3040);
      local_28 = local_40 + *(float *)(local_54 + 0x3040);
      local_24 = local_3c;
      local_20 = local_44 + *(float *)(local_54 + 0x3040);
      local_1c = local_40 - *(float *)(local_54 + 0x3040);
      local_18 = local_3c;
      local_14 = local_44 - *(float *)(local_54 + 0x3040);
      local_10 = local_40 - *(float *)(local_54 + 0x3040);
      local_c = local_3c;
      local_60 = DAT_00920ef4;
      DAT_00920ef4 = local_3c - *(float *)(local_54 + 0x3040);
      FUN_0068d2f0(param_2,*(int *)(local_54 + 0x3030) + *(int *)(local_5c + 5),&local_38,4);
      DAT_00920ef4 = (float)local_60;
    }
  }
  FUN_0083e885();
  return;
}

