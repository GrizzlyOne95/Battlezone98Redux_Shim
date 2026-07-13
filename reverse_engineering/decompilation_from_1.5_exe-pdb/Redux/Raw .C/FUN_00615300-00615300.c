
void FUN_00615300(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float *pfVar3;
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
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
  if (DAT_02cf4000 != 0) {
    puVar1 = (undefined4 *)FUN_00440210(local_58,&DAT_02ceb830,param_1 + 0x40);
    local_44 = *puVar1;
    local_40 = puVar1[1];
    local_3c = (float)puVar1[2];
    if (*(float *)(param_1 + 0x108) <= local_3c) {
      iVar2 = FUN_0068f090(DAT_02cf4000);
      local_48 = ((float)iVar2 * DAT_02ce99c8) / 480.0;
      iVar2 = FUN_0068f0c0(DAT_02cf4000);
      local_4c = ((float)iVar2 * DAT_02ce99c8) / 480.0;
      pfVar3 = (float *)FUN_004400d0(local_64,DAT_02ce99c8,local_44,local_40,local_3c);
      local_30 = pfVar3[2];
      local_38 = *pfVar3 - local_48 * 0.5;
      local_34 = local_4c * 0.5 + pfVar3[1];
      local_2c = local_38 + local_48;
      local_1c = local_34 - local_4c;
      local_14 = local_2c - local_48;
      local_28 = local_34;
      local_24 = local_30;
      local_20 = local_2c;
      local_18 = local_30;
      local_10 = local_1c;
      local_c = local_30;
      FUN_0068d2f0(param_1,DAT_02cf4000,&local_38,4);
    }
  }
  FUN_0083e885();
  return;
}

