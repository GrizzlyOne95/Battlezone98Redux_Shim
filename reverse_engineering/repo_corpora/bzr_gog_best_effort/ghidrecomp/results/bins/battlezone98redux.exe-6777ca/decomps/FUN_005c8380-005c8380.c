
void FUN_005c8380(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar2 = &DAT_008fe1e0;
  puVar3 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00462160(local_48,param_3);
  FUN_005c82b0(param_1,param_2,local_48,param_4);
  FUN_0083e885();
  return;
}

