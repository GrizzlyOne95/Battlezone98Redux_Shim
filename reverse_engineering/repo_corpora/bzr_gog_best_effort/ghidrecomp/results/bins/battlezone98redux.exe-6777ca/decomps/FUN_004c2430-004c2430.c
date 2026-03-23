
void __fastcall FUN_004c2430(int param_1)

{
  int iVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  uint local_28;
  uint local_20;
  undefined **local_1c;
  undefined4 local_14 [2];
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_009454a4 != 0) {
    if (DAT_00919855 != '\0') {
      if ((DAT_009454ac == 0) && (*(int *)(param_1 + 0x4148) != 0)) {
        FUN_004c7320();
      }
      if ((DAT_009454ac != 0) && (*(int *)(param_1 + 0x4154) != 0)) {
        FUN_004c74a0();
      }
    }
    if (DAT_00919863 != '\0') {
      local_20 = (uint)(DAT_009454ac == 0);
      DAT_009454ac = local_20;
      if (local_20 == 0) {
        *(undefined ***)(param_1 + 8) = &PTR_PTR_008e8204;
      }
      else {
        *(undefined ***)(param_1 + 8) = &PTR_PTR_008e8124;
      }
    }
    if (DAT_00919866 != '\0') {
      DAT_009454a8 = (DAT_009454a8 + 1) % 3;
    }
    if (DAT_00919867 != '\0') {
      local_28 = (uint)(*(int *)(param_1 + 0xcc) == 0);
      *(uint *)(param_1 + 0xcc) = local_28;
      FUN_004c1c50();
    }
    if (DAT_009454ac == 0) {
      local_1c = &PTR_PTR_008e8204;
    }
    else {
      local_1c = &PTR_PTR_008e8124;
    }
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 8) + 0x18);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x10) * 0x24 + **(int **)(param_1 + 0xc);
    FUN_004c6760(DAT_009175a0,DAT_009175a4);
    iVar3 = FUN_004c64f0();
    if ((((iVar3 == 0) && (iVar3 = FUN_004c3a00(local_1c), iVar3 == 0)) &&
        (iVar3 = FUN_004c2770(local_1c), iVar3 == 0)) &&
       (iVar3 = FUN_004c7010(local_14,&DAT_009175a0,DAT_00917594), iVar3 != 0)) {
      FUN_0049bf10(local_14[0]);
      uVar4 = FUN_0083f040();
      *(undefined4 *)(param_1 + 0x38) = uVar4;
      FUN_0049bf10(local_c);
      uVar4 = FUN_0083f040();
      *(undefined4 *)(param_1 + 0x3c) = uVar4;
      if (DAT_00919864 != '\0') {
        FUN_004c7bf0(local_14);
      }
      if (DAT_00919865 != '\0') {
        FUN_004c7f80(local_14);
      }
      if (DAT_009454ac == 0) {
        FUN_004c4fa0(local_14);
      }
      else {
        fVar6 = (float10)FUN_004c5430(local_14);
        *(float *)(param_1 + 0xe8) = (float)fVar6;
        FUN_004c83e0();
      }
      FUN_004c2b00();
      FUN_004c3bf0(local_14);
    }
    FUN_004c2860(local_1c);
    FUN_004c5be0();
    fVar2 = DAT_00920ef4;
    DAT_00920ef4 = DAT_00920ef4 + 0.001;
    iVar3 = *(int *)(param_1 + 0x14);
    iVar5 = FUN_0068f0c0(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x10),0x200001,0);
    iVar1 = *(int *)(param_1 + 0x14);
    iVar3 = FUN_0068f090(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x10),
                         (iVar5 * *(int *)(iVar3 + 8)) / 2 + DAT_009175a4);
    FUN_0068c0f0(DAT_00917580,*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x10),
                 (iVar3 * *(int *)(iVar1 + 4)) / 2 + DAT_009175a0);
    DAT_00920ef4 = fVar2;
  }
  FUN_0083e885();
  return;
}

