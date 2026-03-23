
void FUN_005e18a0(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
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
    iVar1 = FUN_0045bdf0();
    if (iVar1 != 0) {
      iVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
      if (-1 < iVar1) {
        uVar2 = FUN_0045c4b0();
        if ((uVar2 & 0x200) == 0) {
          *(uint *)(*(int *)(local_cc + 0x14) + 0x14) =
               *(uint *)(*(int *)(local_cc + 0x14) + 0x14) & 0xfffffdff;
          *(undefined4 *)(local_cc + 0x78) = *(undefined4 *)(*(int *)(local_cc + 0xc) + 0xd0);
          uVar3 = FUN_00462380();
          *(undefined4 *)(local_cc + 0xf0) = uVar3;
          uVar3 = FUN_0045c4d0();
          puVar4 = (undefined4 *)FUN_008203f0(local_10c,uVar3);
          puVar5 = local_c8;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar4 = local_c8;
          puVar5 = local_48;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar4 = (undefined4 *)FUN_0081fe60(local_14c,*(int *)(local_cc + 0x14) + 0x20,local_48);
          puVar5 = local_88;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar4 = local_88;
          puVar5 = (undefined4 *)(local_cc + 0xf8);
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          *(uint *)(*(int *)(local_cc + 0x14) + 0x14) =
               *(uint *)(*(int *)(local_cc + 0x14) + 0x14) & 0xfffffff7;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

