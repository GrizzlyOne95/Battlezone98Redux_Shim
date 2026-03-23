
void FUN_0068ca30(int param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,uint param_8)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 local_84;
  undefined4 local_80;
  float local_7c;
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
  if ((param_3 < 0) || (DAT_00920f00 <= param_3)) {
    param_3 = 0;
  }
  param_3 = param_3 * 0x24;
  local_6c = &DAT_025f8f38 + param_3;
  if ((param_8 & 0x10000) == 0) {
    if ((param_8 & 0x20000) != 0) {
      param_4 = param_4 - param_6;
    }
  }
  else {
    param_4 = param_4 - (param_6 >> 1);
  }
  if ((param_8 & 0x40000) == 0) {
    if ((param_8 & 0x80000) != 0) {
      param_5 = param_5 - param_7;
    }
  }
  else {
    param_5 = param_5 - (param_7 >> 1);
  }
  local_84 = *(undefined4 *)(&DAT_025f8f4c + param_3);
  local_80 = *(undefined4 *)(&DAT_025f8f54 + param_3);
  local_74 = *(undefined4 *)(&DAT_025f8f50 + param_3);
  local_70 = *(undefined4 *)(&DAT_025f8f48 + param_3);
  if ((param_8 & 0x100000) != 0) {
    local_74 = *(undefined4 *)(&DAT_025f8f48 + param_3);
    local_70 = *(undefined4 *)(&DAT_025f8f50 + param_3);
  }
  if ((param_8 & 0x200000) != 0) {
    param_4 = param_4 + *(int *)(param_1 + 8);
    param_5 = param_5 + *(int *)(param_1 + 0xc);
    iVar1 = FUN_0068bf30(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                         *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14),&param_4,
                         &param_5,&param_6,&param_7,&local_70,&local_84,&local_74,&local_80,
                         (int)*(short *)(&DAT_025f8f46 + param_3),
                         (int)*(short *)(&DAT_025f8f44 + param_3));
    if (iVar1 == 0) goto LAB_0068ce69;
  }
  local_7c = (float)param_4;
  fVar2 = (float)param_5;
  fVar3 = (float)param_6 + local_7c;
  fVar4 = (float)param_7;
  FUN_0068b050();
  local_78 = 1.0 / DAT_00920ef4;
  local_68 = local_7c;
  uStack_5c = local_70;
  uStack_58 = local_84;
  uStack_54 = 0x3f800000;
  uStack_44 = local_74;
  uStack_40 = local_84;
  uStack_3c = 0x3f800000;
  uStack_2c = local_74;
  uStack_28 = local_80;
  uStack_24 = 0x3f800000;
  fStack_20 = local_7c;
  uStack_14 = local_70;
  uStack_10 = local_80;
  uStack_c = 0x3f800000;
  DAT_00920efc = (&PTR_DAT_008ed788)[*(uint *)(local_6c + 0x20) & 0xf];
  fStack_64 = fVar2;
  fStack_60 = local_78;
  fStack_50 = fVar3;
  fStack_4c = fVar2;
  fStack_48 = local_78;
  fStack_38 = fVar3;
  fStack_34 = fVar4 + fVar2;
  fStack_30 = local_78;
  fStack_1c = fVar4 + fVar2;
  fStack_18 = local_78;
  DAT_00920efc = (undefined *)FUN_0068f030(param_8,DAT_00920efc);
  iVar1 = FUN_00684ce0(0);
  if (iVar1 != 0) {
    FUN_00686520(param_2,DAT_00920ef4);
    FUN_00686600(0,&local_68,4,DAT_00920efc);
    FUN_006856e0();
  }
  DAT_00920efc = (undefined *)0xffffff;
LAB_0068ce69:
  FUN_0083e885();
  return;
}

