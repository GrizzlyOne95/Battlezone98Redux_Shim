
void FUN_004df3b0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  float10 fVar5;
  undefined1 local_1ec [4];
  undefined1 local_1e8 [4];
  undefined1 local_1e4 [4];
  undefined1 local_1e0 [4];
  undefined1 local_1dc [4];
  undefined1 local_1d8 [4];
  float local_1d4;
  float local_1d0;
  int local_1cc;
  float local_1c8;
  int local_1c4;
  uint local_1c0;
  undefined4 local_1bc;
  int local_1b8;
  uint local_1b4;
  undefined4 auStack_1b0 [66];
  int local_a8;
  float fStack_a4;
  undefined1 auStack_a0 [152];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c0 = 0;
  if (DAT_00917f8c != '\0') {
    memset(&local_a8,0,0xa0);
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin(local_1e4);
    local_1bc = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_1e8);
      cVar1 = FID_conflict_operator__(uVar3);
      if ((cVar1 == '\0') || (0x15 < local_1c0)) break;
      piVar4 = (int *)FUN_00421ec0();
      local_1c4 = *piVar4;
      if (((local_1c4 != 0) && (cVar1 = FUN_004b9830(), cVar1 != '\0')) &&
         (*(char *)(local_1c4 + 0x78) != '\0')) {
        puVar2 = (undefined4 *)(**(code **)(*(int *)(local_1c4 + 0x18) + 0xc))();
        auStack_1b0[local_1c0 * 3] = *puVar2;
        auStack_1b0[local_1c0 * 3 + 1] = puVar2[1];
        auStack_1b0[local_1c0 * 3 + 2] = puVar2[2];
        local_1c0 = local_1c0 + 1;
      }
      FUN_0046b260(local_1ec,0);
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_1e0);
    local_1bc = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_1dc);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_1b8 = *piVar4;
      if ((local_1b8 != 0) && (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
        local_1d0 = 250.0;
        for (local_1cc = 0; local_1cc < (int)local_1c0; local_1cc = local_1cc + 1) {
          puVar2 = (undefined4 *)
                   (**(code **)(*(int *)(local_1b8 + 0x18) + 0xc))
                             (auStack_1b0[local_1cc * 3],auStack_1b0[local_1cc * 3 + 1],
                              auStack_1b0[local_1cc * 3 + 2]);
          fVar5 = (float10)FUN_004976f0(*puVar2,puVar2[1],puVar2[2]);
          local_1d4 = (float)fVar5;
          if (local_1d4 < local_1d0) {
            local_1d0 = local_1d4;
          }
        }
        fVar5 = (float10)FUN_00822da0(local_1d0);
        fVar5 = (float10)(**(code **)(*(int *)(local_1b8 + 0x18) + 0x18))((float)fVar5);
        local_1c8 = (float)fVar5;
        if (0.0 <= local_1c8) {
          for (local_1b4 = 0; local_1b4 < 0x14; local_1b4 = local_1b4 + 1) {
            if ((&local_a8)[local_1b4 * 2] == 0) {
              (&local_a8)[local_1b4 * 2] = local_1b8;
              *(float *)(auStack_a0 + local_1b4 * 8 + -4) = local_1c8;
              break;
            }
            if (*(float *)(auStack_a0 + local_1b4 * 8 + -4) <= local_1c8 &&
                local_1c8 != *(float *)(auStack_a0 + local_1b4 * 8 + -4)) {
              if (local_1b4 < 0x13) {
                memmove(auStack_a0 + local_1b4 * 8,&local_a8 + local_1b4 * 2,
                        (0x14 - local_1b4) * 8 - 8);
              }
              (&local_a8)[local_1b4 * 2] = local_1b8;
              *(float *)(auStack_a0 + local_1b4 * 8 + -4) = local_1c8;
              break;
            }
          }
        }
      }
      FUN_0046b260(local_1d8,0);
    }
    FUN_004b9da0(&local_a8,0x14);
  }
  FUN_0083e885();
  return;
}

