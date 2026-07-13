
void __fastcall FUN_004ab290(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_5c [24];
  undefined4 local_44;
  int local_40;
  int local_3c;
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
  local_44 = param_1;
  for (local_40 = 0; local_40 < 5; local_40 = local_40 + 1) {
    local_3c = FUN_00417f60(local_40);
    if (local_3c != 0) {
      puVar1 = (undefined4 *)FUN_00447f60(local_5c,*(int *)(local_3c + 0x10) + 0x20);
      local_38 = *puVar1;
      local_34 = puVar1[1];
      local_30 = puVar1[2];
      local_2c = puVar1[3];
      local_28 = puVar1[4];
      local_24 = puVar1[5];
      puVar1 = &DAT_008fe1e0;
      puVar3 = (undefined4 *)(*(int *)(local_3c + 0x10) + 0x20);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      local_20 = local_38;
      local_1c = local_34;
      local_18 = local_30;
      local_14 = local_2c;
      local_10 = local_28;
      local_c = local_24;
      FUN_0044b7d0(*(int *)(local_3c + 0x10) + 0x20,&local_38);
    }
  }
  FUN_0083e885();
  return;
}

