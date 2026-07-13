
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00444220(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  int aiStack_6c [7];
  undefined1 local_4c [12];
  undefined1 *local_40;
  float local_3c;
  undefined1 *local_38;
  undefined1 *local_34;
  undefined1 *local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  undefined4 *local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint *local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = *(int *)(param_1 + 100);
  aiStack_6c[6] = 0x444246;
  iVar2 = *(int *)(local_28 + 4) * -0xc;
  local_40 = &stack0xffffffb0 + iVar2;
  local_30 = &stack0xffffffb0 + iVar2;
  iVar1 = *(int *)(local_28 + 4);
  aiStack_6c[*(int *)(local_28 + 4) * -3 + 6] = 0x44425c;
  iVar1 = iVar1 * -2;
  local_38 = &stack0xffffffb0 + iVar1 + iVar2;
  local_34 = &stack0xffffffb0 + iVar1 + iVar2;
  local_18 = 0;
  local_14 = 0;
  do {
    if (*(uint *)(local_28 + 4) <= local_14) {
      local_1c = 0;
      local_2c = 0;
      for (local_c = *(int *)(local_28 + 0x14); local_c != 0; local_c = *(int *)(local_c + 0x30)) {
        if (2 < *(uint *)(local_c + 4)) {
          local_1c = local_1c + *(int *)(local_c + 4);
          local_2c = local_2c + 1;
        }
      }
      local_1c = (local_1c & 1) + local_1c;
      *(uint *)((int)aiStack_6c + iVar1 + iVar2 + 0x18) =
           local_18 * 0xc + 0x18 + local_1c * 2 + local_2c * 0x18;
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x14) = 0x4443b6;
      local_10 = malloc(*(size_t *)((int)aiStack_6c + iVar1 + iVar2 + 0x18));
      if (local_10 != (uint *)0x0) {
        *local_10 = local_18;
        local_10[1] = (uint)(local_10 + 6);
        local_10[2] = local_1c;
        local_10[3] = local_18 * 0xc + local_10[1];
        local_10[4] = local_2c;
        local_10[5] = local_10[3] + local_1c * 2;
        *(uint *)((int)aiStack_6c + iVar1 + iVar2 + 0x18) = local_18 * 0xc;
        *(undefined1 **)((int)aiStack_6c + iVar1 + iVar2 + 0x14) = local_30;
        *(uint *)((int)aiStack_6c + iVar1 + iVar2 + 0x10) = local_10[1];
        *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0xc) = 0x444426;
        memcpy(*(void **)((int)aiStack_6c + iVar1 + iVar2 + 0x10),
               *(void **)((int)aiStack_6c + iVar1 + iVar2 + 0x14),
               *(size_t *)((int)aiStack_6c + iVar1 + iVar2 + 0x18));
        local_1c = 0;
        local_20 = (undefined4 *)local_10[5];
        for (local_c = *(int *)(local_28 + 0x14); iVar3 = local_c, local_c != 0;
            local_c = *(int *)(local_c + 0x30)) {
          if (2 < *(uint *)(local_c + 4)) {
            *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x10) = *(undefined4 *)(local_c + 0xc)
            ;
            *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x14) = *(undefined4 *)(iVar3 + 0x10);
            *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x18) = *(undefined4 *)(iVar3 + 0x14);
            *(undefined1 **)((int)aiStack_6c + iVar1 + iVar2 + 0xc) = local_4c;
            *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 8) = 0x444486;
            puVar4 = (undefined4 *)FUN_00440060();
            *local_20 = *puVar4;
            local_20[1] = puVar4[1];
            local_20[2] = puVar4[2];
            local_20[3] = *(uint *)(local_c + 0x18) ^ 0x80000000;
            local_18 = *(uint *)(local_c + 4);
            local_20[4] = local_18;
            local_20[5] = local_10[3] + local_1c * 2;
            for (local_14 = 0; local_14 < local_18; local_14 = local_14 + 1) {
              *(undefined2 *)(local_20[5] + local_14 * 2) =
                   *(undefined2 *)(local_34 + *(int *)(local_c + 0x40 + local_14 * 0x10) * 2);
            }
            local_1c = local_1c + local_18;
            local_20 = local_20 + 6;
          }
        }
      }
      FUN_0083e885();
      return;
    }
    for (local_24 = 0; local_24 < local_18; local_24 = local_24 + 1) {
      puVar4 = (undefined4 *)(*(int *)(local_28 + 0xc) + local_14 * 0xc);
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x10) = *puVar4;
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x14) = puVar4[1];
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0x18) = puVar4[2];
      puVar4 = (undefined4 *)(local_30 + local_24 * 0xc);
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 4) = *puVar4;
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 8) = puVar4[1];
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2 + 0xc) = puVar4[2];
      *(undefined4 *)((int)aiStack_6c + iVar1 + iVar2) = 0x4442e9;
      fVar6 = (float10)FUN_00444180();
      local_3c = (float)fVar6;
      if ((float)fVar6 < 0.0001) break;
    }
    *(undefined2 *)(local_34 + local_14 * 2) = (undefined2)local_24;
    if (local_24 == local_18) {
      puVar4 = (undefined4 *)(*(int *)(local_28 + 0xc) + local_14 * 0xc);
      puVar5 = (undefined4 *)(local_30 + local_24 * 0xc);
      *puVar5 = *puVar4;
      puVar5[1] = puVar4[1];
      puVar5[2] = puVar4[2];
      local_18 = local_18 + 1;
    }
    local_14 = local_14 + 1;
  } while( true );
}

