
void __thiscall FUN_005d5930(int param_1,undefined4 param_2)

{
  char cVar1;
  float *pfVar2;
  undefined1 local_70 [12];
  undefined4 local_64;
  undefined4 local_60;
  int local_5c;
  undefined8 *local_58;
  float local_54;
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
  local_5c = param_1;
  for (local_58 = (undefined8 *)(param_1 + 0x5030); local_58 < *(undefined8 **)(local_5c + 0x25030);
      local_58 = local_58 + 8) {
    pfVar2 = (float *)FUN_006897e0(local_70,param_2,*local_58,local_58[1],local_58[2]);
    local_54 = *pfVar2;
    local_50 = pfVar2[1];
    local_4c = pfVar2[2];
    local_3c = *(float *)((int)local_58 + 0x34);
    local_48 = local_54;
    local_44 = local_50;
    local_40 = local_4c;
    cVar1 = FUN_004c0560(param_2,&local_48);
    if (cVar1 != '\0') {
      FUN_0049bf10();
      local_64 = FUN_0083f040();
      local_38 = local_48 - local_3c;
      local_34 = local_44 + local_3c;
      local_30 = local_40;
      local_2c = local_48 + local_3c;
      local_28 = local_44 + local_3c;
      local_24 = local_40;
      local_20 = local_48 + local_3c;
      local_1c = local_44 - local_3c;
      local_18 = local_40;
      local_14 = local_48 - local_3c;
      local_10 = local_44 - local_3c;
      local_c = local_40;
      local_60 = DAT_00920ef4;
      DAT_00920ef4 = local_40 - local_3c;
      FUN_0068d2f0(param_2,local_64,&local_38,4);
      DAT_00920ef4 = (float)local_60;
    }
  }
  FUN_0083e885();
  return;
}

