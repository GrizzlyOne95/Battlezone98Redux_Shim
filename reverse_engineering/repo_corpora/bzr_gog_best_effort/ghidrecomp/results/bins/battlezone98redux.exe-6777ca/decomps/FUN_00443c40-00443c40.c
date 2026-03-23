
void FUN_00443c40(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_f4 [12];
  undefined1 local_e8 [12];
  undefined1 local_dc [12];
  undefined1 local_d0 [12];
  undefined1 local_c4 [12];
  undefined1 local_b8 [12];
  undefined1 local_ac [12];
  undefined1 local_a0 [12];
  undefined1 local_94 [12];
  float local_88;
  float local_84;
  int local_80;
  float local_7c;
  int *local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68 [4];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
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
  local_78 = *(int **)(param_1 + 0x28);
  if (local_78 != (int *)0x0) {
    puVar1 = (undefined4 *)FUN_00440000(local_f4,local_78[3],local_78[8],local_78[0xb]);
    local_68[0] = *puVar1;
    local_68[1] = puVar1[1];
    local_68[2] = puVar1[2];
    puVar1 = (undefined4 *)FUN_00440000(local_94,local_78[*local_78 + 2],local_78[8],local_78[0xb]);
    local_68[3] = *puVar1;
    local_58 = puVar1[1];
    local_54 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440000(local_d0,local_78[*local_78 + 2],local_78[8],local_78[local_78[2] + 10]);
    local_50 = *puVar1;
    local_4c = puVar1[1];
    local_48 = puVar1[2];
    puVar1 = (undefined4 *)FUN_00440000(local_b8,local_78[3],local_78[8],local_78[local_78[2] + 10])
    ;
    local_44 = *puVar1;
    local_40 = puVar1[1];
    local_3c = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440000(local_e8,local_78[3],local_78[local_78[1] + 6],local_78[0xb]);
    local_38 = *puVar1;
    local_34 = puVar1[1];
    local_30 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440000(local_a0,local_78[*local_78 + 2],local_78[local_78[1] + 6],local_78[0xb]);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440000(local_ac,local_78[*local_78 + 2],local_78[local_78[1] + 6],
                          local_78[local_78[2] + 10]);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440000(local_c4,local_78[3],local_78[local_78[1] + 6],local_78[local_78[2] + 10])
    ;
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    local_7c = -1e+30;
    for (local_80 = 0; local_80 < 8; local_80 = local_80 + 1) {
      puVar1 = (undefined4 *)
               FUN_004401a0(local_dc,local_68[local_80 * 3],local_68[local_80 * 3 + 1],
                            local_68[local_80 * 3 + 2],*(undefined4 *)(param_1 + 8),
                            *(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x10));
      local_74 = *puVar1;
      local_70 = puVar1[1];
      local_6c = puVar1[2];
      fVar2 = (float10)FUN_004428b0(&local_74,&local_74);
      local_84 = (float)fVar2;
      if (local_7c < local_84) {
        local_7c = local_84;
      }
    }
    fVar2 = (float10)FUN_00417910(local_7c);
    local_88 = (float)fVar2;
    local_7c = local_88 + 0.1;
    if (*(float *)(param_1 + 0x14) <= local_7c && local_7c != *(float *)(param_1 + 0x14)) {
      *(float *)(param_1 + 0x14) = local_7c;
    }
  }
  FUN_0083e885();
  return;
}

