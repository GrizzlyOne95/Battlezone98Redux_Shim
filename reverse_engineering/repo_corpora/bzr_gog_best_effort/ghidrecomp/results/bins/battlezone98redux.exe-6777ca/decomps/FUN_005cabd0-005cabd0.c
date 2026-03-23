
void FUN_005cabd0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_30 [12];
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = FUN_00460fc0(param_2);
  if (local_24 != 0) {
    iVar1 = FUN_00453d10(param_3,0,*(int *)(local_24 + 4) + -1);
    puVar2 = (undefined4 *)
             FUN_004e5270(local_30,*(undefined4 *)(*(int *)(local_24 + 8) + iVar1 * 8),
                          *(undefined4 *)(*(int *)(local_24 + 8) + 4 + iVar1 * 8));
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    FUN_005caa20(param_1,&local_20);
  }
  FUN_0083e885();
  return;
}

