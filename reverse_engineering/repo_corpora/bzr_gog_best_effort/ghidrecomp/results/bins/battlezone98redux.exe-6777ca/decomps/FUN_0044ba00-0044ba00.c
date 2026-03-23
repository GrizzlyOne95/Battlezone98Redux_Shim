
void FUN_0044ba00(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_c0 [24];
  undefined1 local_a8 [16];
  undefined4 local_98 [16];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_0081f530(local_a8,param_2,param_4,param_6);
  local_40 = *puVar1;
  local_3c = puVar1[1];
  local_38 = puVar1[2];
  local_34 = puVar1[3];
  local_30 = local_40;
  local_2c = local_3c;
  local_28 = local_38;
  local_24 = local_34;
  puVar1 = (undefined4 *)FUN_0044b940(local_c0,param_3,param_5,param_6);
  local_58 = *puVar1;
  local_54 = puVar1[1];
  local_50 = puVar1[2];
  local_4c = puVar1[3];
  local_48 = puVar1[4];
  local_44 = puVar1[5];
  local_20 = local_58;
  local_1c = local_54;
  local_18 = local_50;
  local_14 = local_4c;
  local_10 = local_48;
  local_c = local_44;
  FUN_0044b8d0(&local_40,&local_58,local_98);
  puVar1 = local_98;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

