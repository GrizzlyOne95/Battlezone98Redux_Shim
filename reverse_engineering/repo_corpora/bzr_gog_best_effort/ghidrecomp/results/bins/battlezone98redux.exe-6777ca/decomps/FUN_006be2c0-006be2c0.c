
void FUN_006be2c0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_80 [36];
  undefined1 local_5c [4];
  undefined1 local_58 [8];
  undefined4 local_50 [9];
  undefined4 local_2c [8];
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_006c9b00(local_5c);
  puVar2 = (undefined4 *)FUN_006be060(local_80,uVar1);
  puVar4 = local_50;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_50;
  puVar4 = local_2c;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  FUN_006c9b20(local_58);
  local_2c[2] = FUN_006c9950();
  local_2c[1] = FUN_006c9990();
  local_2c[0] = FUN_006c99d0();
  local_c = 0xffffffff;
  puVar2 = local_2c;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

