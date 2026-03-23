
void FUN_0068ce80(int param_1,int param_2,int param_3,int param_4,float param_5,int param_6,
                 int param_7,uint param_8)

{
  int iVar1;
  undefined4 local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined *local_6c;
  float local_68;
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
  float fStack_38;
  float fStack_34;
  float fStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((0 < param_6) && (0 < param_7)) && (DAT_008ed780 <= param_5)) {
    if ((param_2 < 0) || (DAT_00920f00 <= param_2)) {
      param_2 = 0;
    }
    param_2 = param_2 * 0x24;
    local_6c = &DAT_025f8f38 + param_2;
    if ((param_8 & 0x10000) == 0) {
      if ((param_8 & 0x20000) != 0) {
        param_3 = param_3 - (param_6 + -1);
      }
    }
    else {
      param_3 = param_3 - ((param_6 >> 1) + -1);
    }
    if ((param_8 & 0x40000) == 0) {
      if ((param_8 & 0x80000) != 0) {
        param_4 = param_4 - (param_7 + -1);
      }
    }
    else {
      param_4 = param_4 - ((param_7 >> 1) + -1);
    }
    local_88 = *(undefined4 *)(&DAT_025f8f4c + param_2);
    local_7c = *(undefined4 *)(&DAT_025f8f54 + param_2);
    local_74 = *(undefined4 *)(&DAT_025f8f50 + param_2);
    local_70 = *(undefined4 *)(&DAT_025f8f48 + param_2);
    if ((param_8 & 0x100000) != 0) {
      local_74 = *(undefined4 *)(&DAT_025f8f48 + param_2);
      local_70 = *(undefined4 *)(&DAT_025f8f50 + param_2);
    }
    iVar1 = FUN_0068bf30((int)*(float *)(param_1 + 0x14),(int)*(float *)(param_1 + 0x18),
                         (int)*(float *)(param_1 + 0x1c),(int)*(float *)(param_1 + 0x20),&param_3,
                         &param_4,&param_6,&param_7,&local_70,&local_88,&local_74,&local_7c,
                         *(undefined4 *)(param_1 + 0x38),(int)*(short *)(&DAT_025f8f44 + param_2),
                         (int)*(short *)(&DAT_025f8f46 + param_2));
    if (iVar1 != 0) {
      local_84 = (float)param_3;
      local_80 = (float)param_4;
      local_78 = 1.0 / param_5;
      fStack_50 = ((float)param_6 + local_84) - 1.0;
      fStack_34 = ((float)param_7 + local_80) - 1.0;
      uStack_5c = local_70;
      uStack_58 = local_88;
      uStack_54 = 0x3f800000;
      uStack_44 = local_74;
      uStack_40 = local_88;
      uStack_3c = 0x3f800000;
      uStack_2c = local_74;
      uStack_28 = local_7c;
      uStack_24 = 0x3f800000;
      uStack_14 = local_70;
      uStack_10 = local_7c;
      uStack_c = 0x3f800000;
      DAT_00920efc = (&PTR_DAT_008ed788)[*(uint *)(local_6c + 0x20) & 0xf];
      local_68 = local_84;
      fStack_64 = local_80;
      fStack_60 = local_78;
      fStack_4c = local_80;
      fStack_48 = local_78;
      fStack_38 = fStack_50;
      fStack_30 = local_78;
      fStack_20 = local_84;
      fStack_1c = fStack_34;
      fStack_18 = local_78;
      DAT_00920efc = (undefined *)FUN_0068f030(param_8,DAT_00920efc);
      iVar1 = FUN_00684ce0(0);
      if (iVar1 != 0) {
        FUN_00686590(local_6c,param_5);
        FUN_00686600(param_1,&local_68,4,DAT_00920efc);
        FUN_006856e0();
      }
      DAT_00920efc = (undefined *)0xffffff;
    }
  }
  FUN_0083e885();
  return;
}

