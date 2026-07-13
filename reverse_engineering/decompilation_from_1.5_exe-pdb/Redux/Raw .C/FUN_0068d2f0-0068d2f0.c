
void FUN_0068d2f0(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((param_2 < 0) || (DAT_00920f00 <= param_2)) {
    param_2 = 0;
  }
  param_2 = param_2 * 0x24;
  uStack_5c = *(undefined4 *)(&DAT_025f8f48 + param_2);
  uStack_58 = *(undefined4 *)(&DAT_025f8f4c + param_2);
  uStack_44 = *(undefined4 *)(&DAT_025f8f50 + param_2);
  uStack_28 = *(undefined4 *)(&DAT_025f8f54 + param_2);
  local_68 = *param_3;
  local_64 = param_3[1];
  local_60 = param_3[2];
  uStack_54 = 0x3f800000;
  local_50 = param_3[3];
  local_4c = param_3[4];
  local_48 = param_3[5];
  uStack_3c = 0x3f800000;
  local_38 = param_3[6];
  local_34 = param_3[7];
  local_30 = param_3[8];
  uStack_24 = 0x3f800000;
  local_20 = param_3[9];
  local_1c = param_3[10];
  local_18 = param_3[0xb];
  uStack_c = 0x3f800000;
  DAT_00920efc = (&PTR_DAT_008ed788)[*(uint *)(&DAT_025f8f58 + param_2) & 0xf];
  uStack_40 = uStack_58;
  uStack_2c = uStack_44;
  uStack_14 = uStack_5c;
  uStack_10 = uStack_28;
  DAT_00920efc = (undefined *)FUN_0068f030(param_4,DAT_00920efc);
  iVar1 = FUN_00684ce0(0);
  if (iVar1 != 0) {
    FUN_006855e0(&DAT_025f8f38 + param_2,DAT_00920ef4);
    FUN_00686830(param_1,&local_68,4,DAT_00920efc);
    FUN_006856e0();
  }
  DAT_00920efc = (undefined *)0xffffff;
  FUN_0083e885();
  return;
}

