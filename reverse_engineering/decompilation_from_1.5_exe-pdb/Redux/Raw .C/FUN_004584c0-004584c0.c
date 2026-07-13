
void __thiscall FUN_004584c0(int param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_108 [64];
  undefined1 local_c8 [12];
  undefined1 local_bc [12];
  undefined1 local_b0 [12];
  float local_a4;
  undefined4 *local_a0;
  undefined4 local_9c;
  float local_98;
  undefined4 *local_94;
  void *local_90;
  void *local_8c;
  int local_88;
  void *local_84;
  float local_80;
  undefined4 *local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c [16];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_88 = param_1;
  if ((*(char *)(param_2 + 0x1c) != '\0') &&
     (*(float *)(param_2 + 0x7c) <= 1.0 && *(float *)(param_2 + 0x7c) != 1.0)) {
    puVar1 = (undefined4 *)FUN_00439de0(local_b0);
    local_78 = *puVar1;
    local_74 = puVar1[1];
    local_70 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_004401a0(local_bc,local_78,local_74,local_70,*(undefined4 *)(param_2 + 0x84),
                          *(undefined4 *)(param_2 + 0x88));
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    local_20 = local_2c;
    local_1c = local_28;
    local_18 = local_24;
    puVar1 = (undefined4 *)FUN_00439de0(local_c8);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *(undefined4 *)(param_2 + 0x84) = local_14;
    *(undefined4 *)(param_2 + 0x88) = local_10;
    *(undefined4 *)(param_2 + 0x8c) = local_c;
    fVar5 = (float10)FUN_004428b0(&local_2c);
    local_80 = (float)fVar5;
    if (0.0001 <= local_80) {
      if (local_88 != -0x104) {
        fVar5 = (float10)FUN_00820570((double)local_80);
        local_a4 = (float)fVar5;
        local_80 = local_a4 * local_80;
        *(float *)(param_2 + 0x80) =
             *(float *)(local_88 + 0x180) * local_80 + *(float *)(param_2 + 0x80);
        local_98 = local_a4;
      }
      local_a0 = (undefined4 *)FUN_00456f00();
      local_7c = local_a0;
      puVar1 = (undefined4 *)FUN_0081fa10(local_108,param_2 + 0x84);
      puVar4 = local_6c;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar1 = local_6c;
      puVar4 = local_7c;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      local_7c[0x10] = *(undefined4 *)(param_2 + 0x7c);
      local_7c[0x11] = *(undefined4 *)(param_2 + 0x80);
      if ((*(uint *)(param_2 + 0x74) < 2) || (uVar2 = FUN_00822a60(), (uVar2 & 7) == 0)) {
        if (*(uint *)(param_2 + 0x74) < 0x101) {
          if (*(uint *)(param_2 + 0x78) <= *(uint *)(param_2 + 0x74)) {
            *(int *)(param_2 + 0x78) = *(int *)(param_2 + 0x78) << 1;
            local_90 = (void *)FUN_0083d92c();
            local_84 = local_90;
            memset(local_90,0,*(int *)(param_2 + 0x78) << 2);
            memcpy(local_84,*(void **)(param_2 + 0x70),*(int *)(param_2 + 0x74) << 2);
            local_8c = *(void **)(param_2 + 0x70);
            operator_delete__(local_8c);
            *(void **)(param_2 + 0x70) = local_84;
          }
          *(undefined4 **)(*(int *)(param_2 + 0x70) + *(int *)(param_2 + 0x74) * 4) = local_7c;
          *(int *)(param_2 + 0x74) = *(int *)(param_2 + 0x74) + 1;
        }
        else {
          FUN_007d6a70();
          local_94 = local_7c;
          FUN_00456f20();
        }
      }
      else if (*(int *)(param_2 + 0x74) != 0) {
        local_9c = *(undefined4 *)(*(int *)(param_2 + 0x70) + -4 + *(int *)(param_2 + 0x74) * 4);
        FUN_00456f20();
        *(undefined4 **)(*(int *)(param_2 + 0x70) + -4 + *(int *)(param_2 + 0x74) * 4) = local_7c;
      }
    }
  }
  FUN_0083e885();
  return;
}

