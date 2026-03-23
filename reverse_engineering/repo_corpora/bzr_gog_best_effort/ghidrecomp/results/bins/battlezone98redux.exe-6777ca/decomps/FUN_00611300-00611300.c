
void __thiscall FUN_00611300(undefined4 *param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_e8 [64];
  undefined1 local_a8 [12];
  undefined4 *local_9c;
  undefined4 *local_98;
  undefined1 local_94 [64];
  undefined4 local_54 [16];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *param_1 = Weapon::vftable;
  param_1[2] = param_3;
  param_1[4] = param_2;
  local_9c = param_1;
  local_98 = param_1;
  FUN_00438be0(&local_9c);
  local_98[3] = *(undefined4 *)(param_3 + 0x30);
  uVar1 = FUN_00618b60(param_2);
  local_98[5] = uVar1;
  uVar1 = FUN_0062e050(local_98[5]);
  local_98[6] = uVar1;
  puVar2 = (undefined4 *)FUN_00440000(local_a8,0,0,0);
  local_14 = *puVar2;
  local_10 = puVar2[1];
  local_c = puVar2[2];
  local_98[7] = local_14;
  local_98[8] = local_10;
  local_98[9] = local_c;
  puVar2 = (undefined4 *)FUN_006116a0(local_94,0);
  puVar4 = local_98 + 10;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined4 *)FUN_008203f0(local_e8,local_98 + 10);
  puVar4 = local_54;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_54;
  puVar4 = local_98 + 0x1a;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  local_98[0x2a] = *(undefined4 *)(param_3 + 0x68);
  local_98[0x2b] = 0xf149f2ca;
  local_98[0x2c] = *(undefined4 *)(param_3 + 0x34);
  local_98[0x2d] = 0;
  local_98[0x2e] = 1;
  FUN_0083e885();
  return;
}

