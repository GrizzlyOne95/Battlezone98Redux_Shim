
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00615830(undefined4 param_1,float *param_2,uint param_3)

{
  float *pfVar1;
  undefined1 local_d0 [16];
  undefined4 local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined4 local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float fStack_94;
  float fStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_ac = CONCAT22(local_ac._2_2_,0xff00);
  local_ac = CONCAT31(local_ac._1_3_,0xff);
  local_98 = param_2[5];
  fStack_94 = param_2[6];
  fStack_90 = 1.0 / _DAT_008ead08;
  uStack_8c = 0;
  uStack_88 = 0;
  uStack_84 = local_ac;
  fStack_80 = param_2[7];
  fStack_7c = param_2[6];
  fStack_78 = 1.0 / _DAT_008ead08;
  uStack_74 = 0;
  uStack_70 = 0;
  uStack_6c = local_ac;
  fStack_68 = param_2[7];
  fStack_64 = param_2[8];
  fStack_60 = 1.0 / _DAT_008ead08;
  uStack_5c = 0;
  uStack_58 = 0;
  uStack_54 = local_ac;
  fStack_50 = param_2[5];
  fStack_4c = param_2[8];
  fStack_48 = 1.0 / _DAT_008ead08;
  uStack_44 = 0;
  uStack_40 = 0;
  uStack_3c = local_ac;
  local_a8 = 0.0;
  local_a4 = 1.0;
  local_a0 = 0.0;
  local_9c = (float)(param_3 ^ 0x80000000);
  pfVar1 = (float *)FUN_008202b0(local_d0,&local_a8,param_2 + 0x10);
  local_a8 = *pfVar1;
  local_a4 = pfVar1[1];
  local_a0 = pfVar1[2];
  local_9c = pfVar1[3];
  local_b0 = local_a8 / param_2[2];
  local_bc = local_a4 / param_2[3];
  local_b8 = (local_a0 - (local_a8 * *param_2) / param_2[2]) - (local_a4 * param_2[1]) / param_2[3];
  local_b4 = local_9c / param_2[0x4e] + local_b8;
  local_c0 = FUN_00615560(param_1,&local_98,local_b0,local_bc,local_b4,local_ac,4);
  FUN_0083e885();
  return;
}

