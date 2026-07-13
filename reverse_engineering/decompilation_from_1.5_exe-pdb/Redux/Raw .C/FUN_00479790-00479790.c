
void __fastcall FUN_00479790(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_84 [24];
  int local_6c;
  int local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54 [16];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_6c = *(int *)(*(int *)(param_1 + 0xf8) + 0x164);
  local_68 = param_1;
  if (local_6c != 0) {
    puVar1 = (undefined4 *)FUN_0045c4d0();
    puVar3 = local_54;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_64 = FUN_004e1190(local_54,*(undefined4 *)(local_68 + 0x174));
    *(uint *)(*(int *)(local_64 + 0x230) + 0x114) =
         *(uint *)(*(int *)(local_64 + 0x230) + 0x114) | 0xc;
    iVar2 = FUN_00572a70();
    if (iVar2 != 0) {
      FUN_004b8460();
    }
    FUN_0045ca50();
    FUN_00461440();
    puVar1 = (undefined4 *)FUN_004795e0();
    local_60 = *puVar1;
    local_5c = puVar1[1];
    local_58 = puVar1[2];
    puVar1 = (undefined4 *)FUN_004462d0(local_84,0x41a00000);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    FUN_0046fb20();
  }
  FUN_0083e885();
  return;
}

