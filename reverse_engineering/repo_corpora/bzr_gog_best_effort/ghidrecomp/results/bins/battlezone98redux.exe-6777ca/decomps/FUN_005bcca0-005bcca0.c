
void __fastcall FUN_005bcca0(int param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined1 local_7c [24];
  undefined1 local_64 [12];
  float local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_58 = 200.0;
  local_54 = param_1;
  puVar1 = (undefined4 *)FUN_00447f60(local_7c,param_1 + 0x28);
  local_50 = *puVar1;
  local_4c = puVar1[1];
  local_48 = puVar1[2];
  local_44 = puVar1[3];
  local_40 = puVar1[4];
  local_3c = puVar1[5];
  local_2c = local_50;
  uStack_28 = local_4c;
  local_24 = local_48;
  uStack_20 = local_44;
  local_1c = local_40;
  uStack_18 = local_3c;
  pfVar2 = (float *)FUN_004560b0(local_64,local_54 + 0x28);
  local_38 = *pfVar2;
  local_34 = pfVar2[1];
  local_30 = pfVar2[2];
  local_14 = local_38;
  local_10 = local_34;
  local_c = local_30;
  iVar3 = FUN_00784620(local_2c,uStack_28,local_24,uStack_20,local_1c,uStack_18,local_38,local_34,
                       local_30,&local_58,0);
  if (iVar3 != 0) {
    *(float *)(local_54 + 0xcc) =
         (float)((double)(local_58 * local_14) + (double)CONCAT44(uStack_28,local_2c));
    *(float *)(local_54 + 0xd0) =
         (float)((double)(local_58 * local_10) + (double)CONCAT44(uStack_20,local_24));
    *(float *)(local_54 + 0xd4) =
         (float)((double)(local_58 * local_c) + (double)CONCAT44(uStack_18,local_1c));
  }
  FUN_0083e885();
  return;
}

