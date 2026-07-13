
void FUN_005c98f0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  float10 fVar4;
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
  local_24 = FUN_00462630(param_1);
  if ((local_24 != 0) && (param_2 != 0)) {
    iVar1 = FUN_00453d10(param_3,0,*(int *)(param_2 + 4) + -1);
    puVar2 = (undefined4 *)
             FUN_004e5270(local_30,*(undefined4 *)(*(int *)(param_2 + 8) + iVar1 * 8),
                          *(undefined4 *)(*(int *)(param_2 + 8) + 4 + iVar1 * 8));
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    uVar3 = (**(code **)(*(int *)(local_24 + 0x18) + 0xc))(&local_20);
    fVar4 = (float10)FUN_00462010(uVar3);
    FUN_00417910((float)fVar4);
  }
  FUN_0083e885();
  return;
}

