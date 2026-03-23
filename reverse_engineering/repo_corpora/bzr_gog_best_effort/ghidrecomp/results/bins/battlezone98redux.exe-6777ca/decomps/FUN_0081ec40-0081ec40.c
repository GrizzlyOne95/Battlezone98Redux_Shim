
void FUN_0081ec40(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  undefined4 local_48 [4];
  undefined4 local_38;
  uint local_34;
  uint local_2c;
  undefined4 local_28;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar2 = &DAT_008fe1e0;
  puVar3 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  uVar4 = FUN_008205a0(param_2);
  local_38 = (undefined4)((ulonglong)uVar4 >> 0x20);
  local_28 = local_38;
  local_2c = (uint)uVar4 ^ 0x80000000;
  local_34 = (uint)uVar4;
  puVar2 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

