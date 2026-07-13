
void __thiscall FUN_004eb7e0(int param_1,float param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_10c [64];
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  undefined8 local_a4;
  undefined8 local_9c;
  undefined8 local_94;
  undefined8 local_8c;
  undefined4 *local_84;
  int local_80;
  int local_7c;
  float local_78;
  float local_74;
  float local_70;
  undefined4 local_6c [16];
  float local_2c;
  uint local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_80 = *(int *)(*(int *)(param_1 + 0x230) + 0xfc);
  local_7c = param_1;
  iVar2 = FUN_00439e70();
  if (*(int *)(local_7c + 0xf0) == iVar2) {
    iVar2 = ___scrt_is_user_matherr_present();
    if (iVar2 == 0) {
      bVar1 = FUN_004e9690();
      if ((1 < bVar1) && (DAT_008ead0c != 0)) {
        local_a4 = FUN_008205a0();
        local_9c = local_a4;
        local_94 = FUN_008205a0();
        local_24 = (float)((ulonglong)local_94 >> 0x20);
        local_2c = (float)local_a4 * local_24;
        local_28 = (uint)local_94 ^ 0x80000000;
        local_24 = local_a4._4_4_ * local_24;
        local_78 = *(float *)(local_7c + 0x150) * -1.0;
        local_74 = *(float *)(local_7c + 0x154) * -1.0;
        local_70 = *(float *)(local_7c + 0x158) * -1.0;
        local_8c = local_94;
        fVar5 = (float10)FUN_004428b0();
        local_a8 = (float)fVar5;
        local_78 = local_a8 * 0.1 + local_78;
        fVar5 = (float10)FUN_004428b0();
        local_b0 = (float)fVar5;
        local_78 = local_78 - *(float *)(local_7c + 0x2d0) * 10.0;
        local_74 = local_74 - *(float *)(local_7c + 0x2d4) * 10.0;
        local_70 = (local_70 - local_b0 * 0.1) - *(float *)(local_7c + 0x2d8) * 10.0;
        fVar5 = (float10)FUN_004428b0();
        local_ac = (float)fVar5;
        local_78 = local_ac * 25.0 + local_78;
        fVar5 = (float10)FUN_004428b0();
        local_b4 = (float)fVar5;
        local_74 = local_74 - local_b4 * 25.0;
        local_70 = local_70 - *(float *)(local_80 + 0x2c) * 25.0;
        puVar3 = (undefined4 *)
                 FUN_00439d00(local_c0,*(undefined4 *)(local_7c + 0x2d0),
                              *(undefined4 *)(local_7c + 0x2d4),*(undefined4 *)(local_7c + 0x2d8),
                              param_2 * 0.5);
        local_20 = *puVar3;
        local_1c = puVar3[1];
        local_18 = puVar3[2];
        *(undefined4 *)(local_7c + 0x2d0) = local_20;
        *(undefined4 *)(local_7c + 0x2d4) = local_1c;
        *(undefined4 *)(local_7c + 0x2d8) = local_18;
        puVar3 = (undefined4 *)
                 FUN_00444d50(local_10c,local_80 + 0x20,*(undefined4 *)(local_7c + 0x2d0));
        puVar4 = local_6c;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar4 = puVar4 + 1;
        }
        puVar3 = local_6c;
        puVar4 = (undefined4 *)(local_80 + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar4 = puVar4 + 1;
        }
        FUN_00681a00();
        puVar3 = (undefined4 *)
                 FUN_00439d00(local_cc,*(undefined4 *)(local_7c + 0x2d0),
                              *(undefined4 *)(local_7c + 0x2d4),*(undefined4 *)(local_7c + 0x2d8),
                              param_2 * 0.5);
        local_14 = *puVar3;
        local_10 = puVar3[1];
        local_c = puVar3[2];
        *(undefined4 *)(local_7c + 0x2d0) = local_14;
        *(undefined4 *)(local_7c + 0x2d4) = local_10;
        *(undefined4 *)(local_7c + 0x2d8) = local_c;
        goto LAB_004ebd4c;
      }
    }
  }
  local_84 = (undefined4 *)(local_80 + 0x20);
  *local_84 = 0x3f800000;
  *(undefined4 *)(local_80 + 0x24) = 0;
  *(undefined4 *)(local_80 + 0x28) = 0;
  *(undefined4 *)(local_80 + 0x2c) = 0;
  *(undefined4 *)(local_80 + 0x30) = 0x3f800000;
  *(undefined4 *)(local_80 + 0x34) = 0;
  *(undefined4 *)(local_80 + 0x38) = 0;
  *(undefined4 *)(local_80 + 0x3c) = 0;
  *(undefined4 *)(local_80 + 0x40) = 0x3f800000;
  *(undefined4 *)(local_7c + 0x2d0) = 0;
  *(undefined4 *)(local_7c + 0x2d4) = 0;
  *(undefined4 *)(local_7c + 0x2d8) = 0;
  iVar2 = FUN_00439e70();
  if (*(int *)(local_7c + 0xf0) == iVar2) {
    FUN_00681a00();
  }
LAB_004ebd4c:
  FUN_0083e885();
  return;
}

