
void FUN_005ca400(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00462630(param_1);
  if (iVar1 != 0) {
    puVar2 = (undefined4 *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    FUN_005ca270(&local_14,iVar1);
  }
  FUN_0083e885();
  return;
}

