
void FUN_0068c0f0(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 local_88;
  undefined4 local_84;
  int local_80;
  float local_7c;
  int local_78;
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
  if ((param_2 < 0) || (DAT_00920f00 <= param_2)) {
    param_2 = 0;
  }
  param_2 = param_2 * 0x24;
  local_6c = &DAT_025f8f38 + param_2;
  local_78 = (int)*(short *)(&DAT_025f8f44 + param_2);
  if ((param_5 & 0x10000) == 0) {
    if ((param_5 & 0x20000) != 0) {
      param_3 = param_3 - local_78;
    }
  }
  else {
    param_3 = param_3 - (local_78 >> 1);
  }
  local_80 = (int)*(short *)(&DAT_025f8f46 + param_2);
  if ((param_5 & 0x40000) == 0) {
    if ((param_5 & 0x80000) != 0) {
      param_4 = param_4 - local_80;
    }
  }
  else {
    param_4 = param_4 - (local_80 >> 1);
  }
  local_84 = *(undefined4 *)(&DAT_025f8f4c + param_2);
  local_88 = *(undefined4 *)(&DAT_025f8f54 + param_2);
  local_74 = *(undefined4 *)(&DAT_025f8f48 + param_2);
  local_70 = *(undefined4 *)(&DAT_025f8f50 + param_2);
  if ((param_5 & 0x100000) != 0) {
    local_74 = *(undefined4 *)(&DAT_025f8f50 + param_2);
    local_70 = *(undefined4 *)(&DAT_025f8f48 + param_2);
  }
  if ((param_5 & 0x200000) != 0) {
    param_3 = param_3 + *(int *)(param_1 + 8);
    param_4 = param_4 + *(int *)(param_1 + 0xc);
    iVar1 = FUN_0068bf30(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                         *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14),&param_3,
                         &param_4,&local_78,&local_80,&local_74,&local_84,&local_70,&local_88,1);
    if (iVar1 == 0) goto LAB_0068c545;
  }
  fVar2 = (float)param_3;
  fVar3 = (float)param_4;
  fVar4 = (float)local_78;
  fVar5 = (float)local_80;
  FUN_0068b050();
  local_7c = 1.0 / DAT_00920ef4;
  uStack_5c = local_74;
  uStack_58 = local_84;
  uStack_54 = 0x3f800000;
  uStack_44 = local_70;
  uStack_40 = local_84;
  uStack_3c = 0x3f800000;
  uStack_2c = local_70;
  uStack_28 = local_88;
  uStack_24 = 0x3f800000;
  uStack_14 = local_74;
  uStack_10 = local_88;
  uStack_c = 0x3f800000;
  DAT_00920efc = (&PTR_DAT_008ed788)[*(uint *)(local_6c + 0x20) & 0xf];
  local_68 = fVar2;
  fStack_64 = fVar3;
  fStack_60 = local_7c;
  fStack_50 = fVar4 + fVar2;
  fStack_4c = fVar3;
  fStack_48 = local_7c;
  fStack_38 = fVar4 + fVar2;
  fStack_34 = fVar5 + fVar3;
  fStack_30 = local_7c;
  fStack_20 = fVar2;
  fStack_1c = fVar5 + fVar3;
  fStack_18 = local_7c;
  DAT_00920efc = (undefined *)FUN_0068f030(param_5,DAT_00920efc);
  iVar1 = FUN_00684ce0(0);
  if (iVar1 != 0) {
    FUN_00686590(local_6c,DAT_00920ef4);
    FUN_00686600(0,&local_68,4,DAT_00920efc);
    FUN_006856e0();
  }
  DAT_00920efc = (undefined *)0xffffff;
LAB_0068c545:
  FUN_0083e885();
  return;
}

