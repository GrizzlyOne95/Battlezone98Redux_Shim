
void FUN_005013f0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_90 [64];
  undefined *local_50;
  undefined *local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = (undefined *)FUN_004ff7a0(param_1,1);
  if (local_4c == (undefined *)0x0) {
    local_4c = &DAT_00871bb0;
  }
  local_50 = (undefined *)FUN_004ff7a0(param_1,2);
  if (local_50 == (undefined *)0x0) {
    local_50 = &DAT_00871bbc;
  }
  puVar1 = (undefined4 *)FUN_0081f920(local_90,local_4c,local_50);
  puVar2 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)FUN_004ff840(param_1);
  puVar1 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  }
  FUN_0083e885();
  return;
}

