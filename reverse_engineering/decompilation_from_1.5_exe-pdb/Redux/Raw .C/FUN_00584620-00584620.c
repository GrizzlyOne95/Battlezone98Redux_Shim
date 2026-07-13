
void FUN_00584620(char *param_1,int param_2,undefined2 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined8 uVar7;
  undefined1 local_154 [76];
  undefined1 local_108 [36];
  undefined4 local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  undefined8 local_c8;
  int local_c0;
  undefined4 local_bc;
  char *local_b8;
  int local_b0;
  char *local_ac;
  char *local_a8;
  int *local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_a8 = param_1;
  local_b8 = param_1 + param_2;
  while ((local_a8 < local_b8 && (local_a8 < local_b8 + -1))) {
    if (((int)*local_a8 & 0x80U) == 0) {
      uVar7 = *(undefined8 *)local_a8;
      local_a8 = local_a8 + 8;
    }
    else {
      uVar7 = FUN_00583ee0();
      local_a8 = local_a8 + 1;
    }
    local_c8 = uVar7;
    local_c0 = FUN_00586c60();
    if (local_c0 == 0) break;
    local_ac = local_a8;
    local_a8 = local_a8 + 0x14;
    if (DAT_009180d8 != 0) {
      fVar6 = (float10)FUN_00822d80();
      FUN_0056fcb0("Now = %f Ordnance = %f",(double)fVar6);
    }
    puVar2 = (undefined4 *)FUN_00625a30(local_154);
    puVar5 = local_94;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar2 = local_94;
    puVar5 = local_54;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    local_b0 = FUN_004b9ab0();
    if (local_b0 == 0) {
      local_bc = 0;
    }
    else {
      local_bc = (**(code **)(*(int *)(local_b0 + 0x18) + 0x30))();
    }
    local_e4 = local_bc;
    FUN_004bcc60();
    FUN_00585840();
    FID_conflict_begin();
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') {
      local_a4 = (int *)FUN_00586ff0();
      FUN_004bcc60();
      FUN_005857e0();
      DAT_00918130 = DAT_00918130 + -1;
      *(undefined2 *)(local_a4 + 0x1f) = param_3;
      *(undefined2 *)((int)local_a4 + 0x7e) = *(undefined2 *)(local_ac + 10);
      iVar4 = (**(code **)(*local_a4 + 0x20))();
      local_a8 = local_a8 + iVar4;
      FUN_00585bb0();
      FUN_00585bf0();
    }
    else {
      iVar4 = FUN_00422150();
      local_a4 = *(int **)(iVar4 + 4);
      puVar2 = local_54;
      puVar5 = (undefined4 *)(local_a4[5] + 0x20);
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar2 = (undefined4 *)FUN_004560b0();
      local_a0 = *puVar2;
      local_9c = puVar2[1];
      local_98 = puVar2[2];
      piVar3 = (int *)FUN_004462d0(local_108,local_a4[8]);
      local_14 = *piVar3;
      local_10 = piVar3[1];
      local_c = piVar3[2];
      local_a4[0xc] = local_14;
      local_a4[0xd] = local_10;
      local_a4[0xe] = local_c;
      iVar4 = (**(code **)(*local_a4 + 0x20))();
      local_a8 = local_a8 + iVar4;
    }
    if (0.0 < *(float *)(local_ac + 0x10) || *(float *)(local_ac + 0x10) == 0.0) {
      fVar6 = (float10)FUN_00822d80();
      local_d8 = (float)fVar6;
      local_d0 = local_d8 - *(float *)(local_ac + 0x10);
      fVar6 = (float10)FUN_00822d60();
      local_e0 = (float)fVar6;
      local_a4[4] = (int)(local_d0 - local_e0);
    }
    else {
      local_dc = -*(float *)(local_ac + 0x10);
      fVar6 = (float10)FUN_00822d60();
      local_d4 = (float)fVar6;
      local_a4[4] = (int)(local_dc - local_d4);
    }
    if ((float)local_a4[4] <= -5.0 && (float)local_a4[4] != -5.0) {
      if (DAT_009180d8 != 0) {
        FUN_0056fcb0();
      }
      local_a4[4] = 0;
    }
    do {
      if ((float)local_a4[4] <= 0.05) break;
      local_a4[4] = (int)((float)local_a4[4] - 0.05);
      (**(code **)(*local_a4 + 0xc))();
      (**(code **)(*local_a4 + 0x10))();
      cVar1 = FUN_00583dc0();
    } while (cVar1 == '\0');
    local_a4[0x20] = 0;
  }
  FUN_0083e885();
  return;
}

