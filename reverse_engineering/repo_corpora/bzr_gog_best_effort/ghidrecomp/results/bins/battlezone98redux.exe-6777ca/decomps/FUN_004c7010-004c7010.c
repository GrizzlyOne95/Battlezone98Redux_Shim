
void FUN_004c7010(float *param_1,int *param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_7c [24];
  undefined1 local_64 [12];
  undefined1 local_58 [16];
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
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
  *param_1 = (float)*(double *)(DAT_00917594 + 0x58);
  param_1[1] = (float)*(double *)(DAT_00917594 + 0x5a);
  param_1[2] = (float)*(double *)(DAT_00917594 + 0x5c);
  local_14 = ((float)*param_2 - *DAT_00917594) / DAT_00917594[2];
  local_10 = ((float)param_2[1] - DAT_00917594[1]) / DAT_00917594[3];
  local_c = 1.0;
  pfVar1 = (float *)FUN_00440300(local_58,&local_14,DAT_00917594 + 0x10);
  local_2c = *pfVar1;
  local_28 = pfVar1[1];
  local_24 = pfVar1[2];
  local_14 = local_2c;
  local_10 = local_28;
  local_c = local_24;
  pfVar1 = (float *)FUN_004621a0(local_64,&local_14);
  local_20 = *pfVar1;
  local_1c = pfVar1[1];
  local_18 = pfVar1[2];
  local_48 = DAT_02ce99c8;
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  puVar2 = (undefined4 *)FUN_0049c4f0(local_7c,*param_1,param_1[1],param_1[2]);
  local_44 = *puVar2;
  local_40 = puVar2[1];
  local_3c = puVar2[2];
  local_38 = puVar2[3];
  local_34 = puVar2[4];
  local_30 = puVar2[5];
  iVar3 = FUN_00784620(local_44,local_40,local_3c,local_38,local_34,local_30,local_14,local_10,
                       local_c,&local_48,0);
  if (iVar3 != 0) {
    *param_1 = local_48 * local_14 + *param_1;
    param_1[1] = local_48 * local_10 + param_1[1];
    param_1[2] = local_48 * local_c + param_1[2];
  }
  FUN_0083e885();
  return;
}

