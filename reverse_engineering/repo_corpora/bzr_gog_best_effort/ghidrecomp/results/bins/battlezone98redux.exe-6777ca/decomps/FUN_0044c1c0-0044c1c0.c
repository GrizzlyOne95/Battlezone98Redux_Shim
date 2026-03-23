
void FUN_0044c1c0(float param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_178 [64];
  undefined1 local_138 [12];
  undefined1 local_12c [12];
  undefined1 local_120 [12];
  undefined1 local_114 [4];
  float local_110;
  undefined4 *local_10c;
  float local_108;
  undefined4 *local_104;
  float local_100;
  undefined4 local_fc;
  float local_f8;
  float local_f4;
  undefined4 *local_f0;
  undefined1 local_ec [4];
  float local_e8;
  int local_e4;
  undefined4 *local_e0;
  undefined4 local_dc [16];
  undefined4 local_9c [16];
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_1 == 0.0) {
    local_f4 = 1e+30;
  }
  else {
    local_f4 = 1.0 / param_1;
  }
  local_e8 = local_f4;
  FUN_00447e20(local_ec);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_114);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_10c = (undefined4 *)FUN_00447e70();
    local_e0 = local_10c;
    FUN_00447e90();
    if (*(char *)(local_e0 + 7) == '\0') {
      local_104 = local_e0;
      local_f0 = local_e0;
      if (local_e0 == (undefined4 *)0x0) {
        local_fc = 0;
      }
      else {
        local_fc = (**(code **)*local_e0)(1);
      }
    }
    else {
      FUN_0044b810(local_e0 + 8,local_e0 + 0x20,local_e0 + 0x2a);
      if ((float)local_e0[0x18] <= param_1 && param_1 != (float)local_e0[0x18]) {
        local_5c = (float)(*(double *)(local_e0 + 0x2a) - *(double *)(local_e0 + 0x24)) * local_e8;
        local_58 = (float)(*(double *)(local_e0 + 0x2c) - *(double *)(local_e0 + 0x26)) * local_e8;
        local_54 = (float)(*(double *)(local_e0 + 0x2e) - *(double *)(local_e0 + 0x28)) * local_e8;
        do {
          puVar3 = (undefined4 *)
                   FUN_0044ba00(local_178,local_e0 + 0x1c,local_e0 + 0x24,local_e0 + 0x20,
                                local_e0 + 0x2a,(float)local_e0[0x18] * local_e8);
          puVar5 = local_dc;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_dc;
          puVar5 = local_9c;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          pfVar4 = (float *)FUN_00440300(local_120,&local_5c,local_9c);
          local_2c = *pfVar4;
          local_28 = pfVar4[1];
          local_24 = pfVar4[2];
          local_14 = *(float *)(local_e4 + 0x110);
          local_20 = local_2c;
          local_1c = local_28;
          local_18 = local_24;
          fVar6 = (float10)FUN_004464c0();
          local_100 = (float)fVar6;
          local_14 = *(float *)(local_e4 + 0x128) * local_2c +
                     local_100 * *(float *)(local_e4 + 0x11c) + local_14;
          local_10 = *(float *)(local_e4 + 0x114);
          fVar6 = (float10)FUN_004464c0();
          local_108 = (float)fVar6;
          local_10 = *(float *)(local_e4 + 300) * local_28 +
                     local_108 * *(float *)(local_e4 + 0x120) + local_10;
          local_c = *(float *)(local_e4 + 0x118);
          fVar6 = (float10)FUN_004464c0();
          local_110 = (float)fVar6;
          local_c = *(float *)(local_e4 + 0x130) * local_24 +
                    local_110 * *(float *)(local_e4 + 0x124) + local_c;
          pfVar4 = (float *)FUN_00440210(local_12c,&local_14,local_9c);
          local_44 = *pfVar4;
          local_40 = pfVar4[1];
          local_3c = pfVar4[2];
          local_14 = local_44;
          local_10 = local_40;
          local_c = local_3c;
          puVar3 = (undefined4 *)FUN_00440000(local_138,0,0,0);
          local_50 = *puVar3;
          local_4c = puVar3[1];
          local_48 = puVar3[2];
          local_38 = local_50;
          local_34 = local_4c;
          local_30 = local_48;
          FUN_004513e0(local_9c,&local_14,&local_50,param_1 - (float)local_e0[0x18]);
          local_e0[0x18] = (float)local_e0[0x18] + *(float *)(local_e4 + 0x108);
          fVar6 = (float10)FUN_004464c0();
          local_f8 = (float)fVar6;
          local_e0[0x18] = local_f8 * *(float *)(local_e4 + 0x10c) + (float)local_e0[0x18];
        } while ((float)local_e0[0x18] <= param_1 && param_1 != (float)local_e0[0x18]);
      }
      local_e0[0x1c] = local_e0[0x20];
      local_e0[0x1d] = local_e0[0x21];
      local_e0[0x1e] = local_e0[0x22];
      local_e0[0x1f] = local_e0[0x23];
      local_e0[0x24] = local_e0[0x2a];
      local_e0[0x25] = local_e0[0x2b];
      local_e0[0x26] = local_e0[0x2c];
      local_e0[0x27] = local_e0[0x2d];
      local_e0[0x28] = local_e0[0x2e];
      local_e0[0x29] = local_e0[0x2f];
      local_e0[0x18] = (float)local_e0[0x18] - param_1;
    }
  }
  FUN_0083e885();
  return;
}

