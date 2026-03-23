
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_007838a0(int param_1)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_ac [16];
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  byte *local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  float local_38;
  int local_34;
  int local_30;
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
  if ((((DAT_009183d4 == 0) && (cVar1 = FUN_0077d3f0(), cVar1 != '\0')) && (DAT_02ceb834 <= 0.999))
     && (0.001 <= DAT_02ceb834)) {
    fVar4 = (float10)FUN_00417910(DAT_02ceb830 * DAT_02ceb830 + DAT_02ceb838 * DAT_02ceb838);
    fVar4 = (float10)FUN_0046e0a0(DAT_02ceb834,(float)fVar4);
    local_2c = (float)fVar4;
    fVar4 = (float10)FUN_0046e0a0(DAT_02ceb838,DAT_02ceb830);
    local_28 = (float)fVar4;
    fVar4 = (float10)FUN_00417910(DAT_02ceb830 * DAT_02ceb830 + DAT_02ceb838 * DAT_02ceb838);
    local_64 = (float)fVar4;
    local_90 = local_64 / DAT_02ceb834;
    pfVar2 = (float *)FUN_0062c8f0(local_ac,param_1);
    local_18 = *pfVar2;
    local_14 = pfVar2[1];
    local_10 = pfVar2[2];
    local_c = pfVar2[3];
    local_38 = (local_c + local_14) * local_90;
    local_44 = (int)((local_18 - local_38) * 0.2 - 1.0);
    local_40 = (int)((local_18 + local_38) * 0.2 + 1.0);
    local_3c = (int)((local_10 - local_38) * 0.2 - 1.0);
    local_48 = (int)((local_10 + local_38) * 0.2 + 1.0);
    if (local_44 < DAT_02ce99c0) {
      local_44 = DAT_02ce99c0;
    }
    if (DAT_02ce99a0 < local_40) {
      local_40 = DAT_02ce99a0;
    }
    if (local_3c < DAT_02cd9984) {
      local_3c = DAT_02cd9984;
    }
    if (DAT_02ce99c4 < local_48) {
      local_48 = DAT_02ce99c4;
    }
    memset(&DAT_02c06980,0,0x50);
    DAT_02c069c0 = DAT_02ceb830;
    DAT_02c069c4 = DAT_02ceb834;
    DAT_02c069c8 = DAT_02ceb838;
    fVar4 = (float10)FUN_004178f0(local_2c);
    local_98 = (float)fVar4;
    local_7c = local_98;
    fVar4 = (float10)FUN_004178b0(local_28 + 3.1415927);
    local_5c = (float)fVar4;
    DAT_02c069a0 = local_7c * local_5c;
    fVar4 = (float10)FUN_004178b0(local_2c);
    DAT_02c069a4 = (float)fVar4;
    fVar4 = (float10)FUN_004178f0(local_2c);
    local_9c = (float)fVar4;
    local_50 = local_9c;
    fVar4 = (float10)FUN_004178f0(local_28 + 3.1415927);
    local_84 = (float)fVar4;
    DAT_02c069a8 = local_50 * local_84;
    fVar4 = (float10)FUN_004178b0(local_2c);
    local_6c = (float)fVar4;
    DAT_02c069ac = local_6c * (*(float *)(param_1 + 0x54) - local_14);
    fVar4 = (float10)FUN_004178f0(local_2c);
    local_94 = (float)fVar4;
    local_74 = -local_94;
    fVar4 = (float10)FUN_004178b0(local_28 + 3.1415927);
    local_8c = (float)fVar4;
    DAT_02c069b0 = local_74 * local_8c;
    fVar4 = (float10)FUN_004178b0(local_2c);
    local_54 = (float)fVar4;
    DAT_02c069b4 = -local_54;
    fVar4 = (float10)FUN_004178f0(local_2c);
    local_58 = (float)fVar4;
    local_60 = -local_58;
    fVar4 = (float10)FUN_004178f0(local_28 + 3.1415927);
    local_68 = (float)fVar4;
    DAT_02c069b8 = local_60 * local_68;
    fVar4 = (float10)FUN_004178b0(local_2c);
    local_70 = (float)fVar4;
    DAT_02c069bc = local_70 * (local_14 - *(float *)(param_1 + 0x48));
    fVar4 = (float10)FUN_004178b0(1.5707964 - local_28);
    DAT_02c069b0 = (float)fVar4;
    DAT_02c069b4 = 0.0;
    fVar4 = (float10)FUN_004178f0(1.5707964 - local_28);
    DAT_02c069b8 = (float)fVar4;
    fVar4 = (float10)fmaxf(*(float *)(param_1 + 0x50) - local_18,
                           *(float *)(param_1 + 0x58) - local_10);
    DAT_02c069bc = (float)fVar4;
    fVar4 = (float10)FUN_004178b0(1.5707964 - local_28);
    local_78 = (float)fVar4;
    DAT_02c06980 = -local_78;
    DAT_02c06984 = 0;
    fVar4 = (float10)FUN_004178f0(1.5707964 - local_28);
    local_80 = (float)fVar4;
    DAT_02c06988 = -local_80;
    fVar4 = (float10)fmaxf(local_18 - *(float *)(param_1 + 0x44),
                           local_10 - *(float *)(param_1 + 0x4c));
    DAT_02c0698c = (float)fVar4;
    for (local_34 = local_3c; local_34 <= local_48; local_34 = local_34 + 1) {
      for (local_30 = local_44; local_30 <= local_40; local_30 = local_30 + 1) {
        local_24 = (float)local_30 * 5.0 - local_18;
        fVar4 = (float10)FUN_0077d410(local_30,local_34);
        local_88 = (float)fVar4;
        local_20 = local_88 * 5.0 - local_14;
        local_1c = (float)local_34 * 5.0 - local_10;
        iVar3 = FUN_00783840(&local_24,&DAT_02c06980);
        if (iVar3 != 0) {
          local_4c = (byte *)FUN_0050ce30(local_30,local_34);
          *local_4c = (byte)(int)((float)*local_4c * _DAT_02cd9448);
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

