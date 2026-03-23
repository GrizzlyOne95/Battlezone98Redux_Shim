
void FUN_005ba200(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_dc [64];
  undefined4 local_9c;
  float local_98;
  int local_94;
  int local_90;
  int local_8c;
  undefined4 local_88 [16];
  undefined4 local_48 [10];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if (iVar1 != 0) {
    local_90 = FUN_00417c70();
    *(undefined4 *)(local_8c + 0xac) = 0;
    *(undefined4 *)(local_8c + 0xa8) = 0;
    if (local_90 == 0) {
      puVar2 = &DAT_008fe1e0;
      puVar3 = (undefined4 *)(local_8c + 0x28);
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = &DAT_008fe1e0;
      puVar3 = (undefined4 *)(local_8c + 0x68);
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    else {
      local_9c = *(undefined4 *)(*(int *)(local_90 + 0x230) + 0xfc);
      local_94 = (**(code **)(*(int *)(local_90 + 0x18) + 0x2c))();
      if (((local_94 == 0) || (*(int *)(local_94 + 0x94) == 0)) || (*(int *)(local_94 + 0xe0) == 0))
      {
        puVar2 = &DAT_008fe1e0;
        puVar3 = (undefined4 *)(local_8c + 0x28);
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = &DAT_008fe1e0;
        puVar3 = (undefined4 *)(local_8c + 0x68);
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
      }
      else {
        puVar2 = (undefined4 *)FUN_0067dac0(local_dc,local_94);
        puVar3 = local_88;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_88;
        puVar3 = local_48;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = (undefined4 *)FUN_0045c4d0();
        puVar3 = (undefined4 *)(local_8c + 0x28);
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        *(undefined8 *)(local_8c + 0x50) = local_20;
        *(undefined8 *)(local_8c + 0x58) = local_18;
        *(undefined8 *)(local_8c + 0x60) = local_10;
        fVar4 = (float10)FUN_00820570((double)(*(float *)(local_8c + 0x40) *
                                               *(float *)(local_8c + 0x40) +
                                               *(float *)(local_8c + 0x48) *
                                               *(float *)(local_8c + 0x48) + 1.1754944e-38));
        local_98 = (float)fVar4;
        *(undefined4 *)(local_8c + 0x74) = 0;
        *(undefined4 *)(local_8c + 0x78) = 0x3f800000;
        *(undefined4 *)(local_8c + 0x7c) = 0;
        *(float *)(local_8c + 0x80) = local_98 * *(float *)(local_8c + 0x40);
        *(undefined4 *)(local_8c + 0x84) = 0;
        *(float *)(local_8c + 0x88) = local_98 * *(float *)(local_8c + 0x48);
        *(undefined4 *)(local_8c + 0x68) = *(undefined4 *)(local_8c + 0x88);
        *(undefined4 *)(local_8c + 0x6c) = 0;
        *(uint *)(local_8c + 0x70) = *(uint *)(local_8c + 0x80) ^ 0x80000000;
        *(undefined8 *)(local_8c + 0x90) = *(undefined8 *)(local_8c + 0x50);
        *(undefined8 *)(local_8c + 0x98) = *(undefined8 *)(local_8c + 0x58);
        *(undefined8 *)(local_8c + 0xa0) = *(undefined8 *)(local_8c + 0x60);
      }
    }
  }
  FUN_0083e885();
  return;
}

