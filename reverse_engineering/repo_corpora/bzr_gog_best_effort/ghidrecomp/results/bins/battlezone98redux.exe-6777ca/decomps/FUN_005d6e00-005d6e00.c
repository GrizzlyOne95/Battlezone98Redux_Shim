
void __thiscall FUN_005d6e00(int param_1,int *param_2,undefined4 param_3)

{
  short sVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  float *pfVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined1 local_fc [64];
  undefined1 local_bc [12];
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  int local_a4;
  undefined4 local_a0 [16];
  undefined4 local_60 [16];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_a4 = param_1;
  if (param_2 == (int *)0x0) goto LAB_005d708b;
  iVar4 = FUN_00572a70();
  if (iVar4 != 0) {
    sVar1 = *(short *)(local_a4 + 0x7c);
    sVar3 = FUN_00572d90();
    if (sVar1 != sVar3) goto LAB_005d708b;
  }
  cVar2 = (**(code **)(*param_2 + 0x14))();
  if (cVar2 == '\0') goto LAB_005d708b;
  local_b0 = *(undefined4 *)(param_2[0x8c] + 0xfc);
  puVar5 = (undefined4 *)FUN_008203f0(local_fc,*(int *)(local_a4 + 0x14) + 0x20);
  puVar8 = local_60;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar5 = local_60;
  puVar8 = local_a0;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  pfVar6 = (float *)FUN_0062e120(local_bc,local_b0);
  local_20 = *pfVar6;
  local_1c = pfVar6[1];
  local_18 = pfVar6[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  FUN_00820180(&local_14,&local_14,1,local_a0);
  if (local_c <= 0.0) goto LAB_005d708b;
  local_14 = local_14 / *(float *)(*(int *)(local_a4 + 0xc) + 0x7c);
  local_10 = local_10 / *(float *)(*(int *)(local_a4 + 0xc) + 0x7c);
  local_c = local_c / *(float *)(*(int *)(local_a4 + 0xc) + 0x78);
  if (1.0 <= local_14 * local_14 + local_10 * local_10 + local_c * local_c) goto LAB_005d708b;
  (**(code **)(*param_2 + 0x78))();
  cVar2 = FUN_004b9830();
  if (cVar2 != '\0') {
    local_a8 = FUN_0046d000();
    if (local_a8 != 0) {
      local_ac = FUN_00479f30(local_a8);
      FUN_00573bb0(local_ac,param_2);
    }
  }
  cVar2 = FUN_004b9860();
  if (cVar2 != '\0') {
    uVar7 = (**(code **)(param_2[6] + 0x30))();
    iVar4 = FUN_0062e000(uVar7);
    if (iVar4 != 0) {
      uVar7 = (**(code **)(param_2[6] + 0x30))();
      iVar4 = FUN_00417e20(uVar7);
      if (iVar4 != 0) {
        cVar2 = (**(code **)(*param_2 + 0x6c))();
        if (cVar2 == '\0') goto LAB_005d706e;
      }
      *(uint *)(*(int *)(local_a4 + 0x14) + 0x14) = *(uint *)(*(int *)(local_a4 + 0x14) + 0x14) | 2;
    }
  }
LAB_005d706e:
  *(uint *)(*(int *)(local_a4 + 0x14) + 0x14) = *(uint *)(*(int *)(local_a4 + 0x14) + 0x14) | 0x200;
LAB_005d708b:
  FUN_00480750(param_2,param_3);
  FUN_0083e885();
  return;
}

