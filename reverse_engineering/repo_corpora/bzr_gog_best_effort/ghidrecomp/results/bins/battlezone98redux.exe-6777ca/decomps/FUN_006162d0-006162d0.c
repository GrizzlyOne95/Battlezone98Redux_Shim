
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006162d0(int param_1,int param_2,float param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_d0 [64];
  double local_90;
  float local_88;
  float local_84;
  double local_80;
  undefined4 local_78;
  double local_74;
  double local_6c;
  float local_64;
  float local_60;
  undefined1 local_5c;
  undefined1 local_5b;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_4c;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_88 = 1.0 / *(float *)(param_2 + 8);
  local_64 = 1.0 / *(float *)(param_2 + 0xc);
  local_60 = *(float *)(param_2 + 0x10) * 0.6;
  local_58 = *(float *)(param_2 + 0x10);
  local_50 = 2;
  local_84 = (local_58 - local_60) / 2.0;
  local_54 = CONCAT22(local_54._2_2_,0xffff);
  local_5c = 0xff;
  local_5b = 0;
  local_78 = 0xc2ff0000;
  puVar1 = &DAT_008fe1e0;
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_90 = *(double *)(param_2 + 0x160) / 1000.0;
  local_6c = floor(local_90);
  local_20 = local_6c * 1000.0;
  local_74 = *(double *)(param_2 + 0x170) / 1000.0;
  local_80 = floor(local_74);
  local_10 = local_80 * 1000.0;
  local_18 = (double)param_3;
  puVar1 = (undefined4 *)FUN_0081fe60(local_d0,local_48,param_2 + 0x40);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  for (local_4c = 0; local_4c < 4; local_4c = local_4c + 1) {
    FUN_00820180(local_4c * 0x18 + param_1,&DAT_008eaa40 + local_4c * 0xc,1,local_48);
    *(float *)(param_1 + 0xc + local_4c * 0x18) =
         (float)_DAT_02a13dd0 + *(float *)(&DAT_008eaa70 + local_4c * 0xc);
    *(float *)(param_1 + 0x10 + local_4c * 0x18) =
         (float)_DAT_02a13de8 + *(float *)(&DAT_008eaa74 + local_4c * 0xc);
    *(undefined4 *)(param_1 + 0x14 + local_4c * 0x18) = local_54;
  }
  FUN_0083e885();
  return;
}

