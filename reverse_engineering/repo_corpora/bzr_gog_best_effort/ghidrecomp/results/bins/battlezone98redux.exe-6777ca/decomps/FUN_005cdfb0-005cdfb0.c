
void FUN_005cdfb0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00462630(param_1);
  if ((iVar1 != 0) && (iVar2 = FUN_00462630(param_2), iVar2 != 0)) {
    puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    local_14 = *puVar3;
    local_10 = puVar3[1];
    local_c = puVar3[2];
    puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    FUN_00462010(&local_14,&local_20);
    (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
    FUN_00462400();
    FUN_00462400();
  }
  FUN_0083e885();
  return;
}

