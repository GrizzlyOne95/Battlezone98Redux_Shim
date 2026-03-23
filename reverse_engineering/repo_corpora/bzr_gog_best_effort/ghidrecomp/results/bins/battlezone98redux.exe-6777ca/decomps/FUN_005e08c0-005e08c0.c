
void FUN_005e08c0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_14c [64];
  undefined1 local_10c [64];
  int local_cc;
  undefined4 local_c8 [16];
  undefined4 local_88 [16];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00480750(param_1,param_2);
  if (param_1 != 0) {
    *(uint *)(*(int *)(local_cc + 0x14) + 0x14) =
         *(uint *)(*(int *)(local_cc + 0x14) + 0x14) & 0xfffffdff;
    *(undefined4 *)(local_cc + 0x78) = *(undefined4 *)(*(int *)(local_cc + 0xc) + 0xd0);
    uVar1 = FUN_00462380();
    *(undefined4 *)(local_cc + 0xf0) = uVar1;
    uVar1 = FUN_0045c4d0();
    puVar2 = (undefined4 *)FUN_008203f0(local_10c,uVar1);
    puVar4 = local_c8;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = local_c8;
    puVar4 = local_48;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = (undefined4 *)FUN_0081fe60(local_14c,*(int *)(local_cc + 0x14) + 0x20,local_48);
    puVar4 = local_88;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = local_88;
    puVar4 = (undefined4 *)(local_cc + 0xf8);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  FUN_0083e885();
  return;
}

