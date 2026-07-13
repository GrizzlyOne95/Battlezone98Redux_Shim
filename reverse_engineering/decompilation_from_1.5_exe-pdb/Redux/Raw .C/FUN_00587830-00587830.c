
void FUN_00587830(float *param_1,int param_2,int param_3,float *param_4)

{
  float *pfVar1;
  undefined1 local_54 [12];
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float fStack_28;
  float local_24;
  float fStack_20;
  float local_1c;
  float fStack_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = param_4[0x58];
  fStack_28 = param_4[0x59];
  local_24 = param_4[0x5a];
  fStack_20 = param_4[0x5b];
  local_1c = param_4[0x5c];
  fStack_18 = param_4[0x5d];
  local_14 = ((float)param_2 - *param_4) / param_4[2];
  local_10 = ((float)param_3 - param_4[1]) / param_4[3];
  local_c = 1.0;
  pfVar1 = (float *)FUN_00440300(local_54,&local_14,param_4 + 0x10);
  local_38 = *pfVar1;
  local_34 = pfVar1[1];
  local_30 = pfVar1[2];
  local_48 = (float)(-(double)CONCAT44(fStack_20,local_24) / (double)local_34);
  local_14 = local_38;
  local_10 = local_34;
  local_c = local_30;
  FUN_00784620(local_2c,fStack_28,local_24,fStack_20,local_1c,fStack_18,local_38,local_34,local_30,
               &local_48,0);
  local_44 = (float)((double)(local_48 * local_14) + (double)CONCAT44(fStack_28,local_2c));
  local_40 = (float)((double)(local_48 * local_10) + (double)CONCAT44(fStack_20,local_24));
  local_3c = (float)((double)(local_48 * local_c) + (double)CONCAT44(fStack_18,local_1c));
  *param_1 = local_44;
  param_1[1] = local_40;
  param_1[2] = local_3c;
  FUN_0083e885();
  return;
}

