
void FUN_005cdcd0(void)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_ac [24];
  undefined4 local_94;
  int local_90;
  int local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c [10];
  double local_54;
  double local_4c;
  double local_44;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_8c = FUN_00462630();
  if (local_8c != 0) {
    puVar1 = (undefined4 *)(**(code **)(*(int *)(local_8c + 0x18) + 0xc))();
    local_30 = *puVar1;
    local_2c = puVar1[1];
    local_28 = puVar1[2];
    local_90 = FUN_00466790();
    if (local_90 != 0) {
      puVar1 = (undefined4 *)FUN_0045c4d0();
      puVar4 = local_7c;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      pfVar2 = (float *)FUN_00462400();
      local_18 = *pfVar2;
      local_14 = pfVar2[1];
      local_10 = pfVar2[2];
      local_c = pfVar2[3];
      FUN_00820180(&local_18);
      local_54 = (double)local_18;
      local_4c = (double)local_14;
      local_44 = (double)local_10;
      FUN_0056d6a0();
      local_94 = FUN_00462490();
      puVar1 = (undefined4 *)FUN_004560b0();
      local_88 = *puVar1;
      local_84 = puVar1[1];
      local_80 = puVar1[2];
      puVar1 = (undefined4 *)FUN_004462d0(local_ac,0x42480000);
      local_3c = *puVar1;
      local_38 = puVar1[1];
      local_34 = puVar1[2];
      local_24 = local_3c;
      local_20 = local_38;
      local_1c = local_34;
      FUN_0046fb20();
      FUN_00477590();
    }
  }
  FUN_0083e885();
  return;
}

