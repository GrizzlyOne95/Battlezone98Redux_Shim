
void __thiscall FUN_004c9ab0(int param_1,undefined4 *param_2,int param_3)

{
  char cVar1;
  undefined4 *puVar2;
  float *pfVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_144 [44];
  undefined1 local_118 [12];
  undefined1 local_10c [12];
  undefined1 local_100 [4];
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  float local_f0;
  int local_ec;
  undefined4 local_e8;
  int local_e4;
  undefined4 *local_e0;
  float local_dc;
  float local_d8;
  undefined4 local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  int local_c4;
  float local_c0;
  int local_bc;
  float *local_b8;
  float local_b4;
  float *local_b0;
  ushort local_aa;
  int local_a8;
  int local_a4;
  byte local_9d;
  int local_9c;
  float local_98;
  undefined4 local_94;
  float local_90;
  undefined1 local_8c [16];
  undefined4 local_7c;
  undefined1 local_60 [4];
  undefined4 local_5c;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
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
  if (param_3 == 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0;
  }
  else {
    *(uint *)(*(int *)(param_1 + 0xc) + 0x14) = *(uint *)(param_3 + 0x14) & 0xf0000;
  }
  puVar2 = (undefined4 *)(*(int *)(param_1 + 0xc) + 0x20);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0xa0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0xa4) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0xa8) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0xac) = *(undefined4 *)(*(int *)(param_1 + 8) + 0x3c);
  *(float *)(param_1 + 0x14) = (float)*(int *)(*(int *)(param_1 + 8) + 0x30);
  *(float *)(param_1 + 0x18) =
       (float)(*(int *)(*(int *)(param_1 + 8) + 0x34) + *(int *)(*(int *)(param_1 + 8) + 0x30));
  local_9c = param_1;
  if (*(char *)(*(int *)(param_1 + 8) + 0x40) != '\0') {
    FUN_0043a990(local_8c);
    local_7c = 0x3000;
    FUN_0043a9e0(local_60);
    local_5c = 0x32;
    FUN_0043aa30();
  }
  *(int *)(local_9c + 0x10) = param_3;
  *(undefined4 *)(local_9c + 0x1c) = 0;
  *(undefined4 *)(local_9c + 0x20) = 0;
  *(undefined4 *)(local_9c + 0x24) = 0;
  *(undefined4 *)(local_9c + 0x28) = 0;
  *(int *)(local_9c + 0x1c) = param_3;
  *(undefined4 *)(local_9c + 0x20) = *(undefined4 *)(local_9c + 0xc);
  local_d4 = FUN_0047e9a0(*(undefined4 *)(local_9c + 0xc));
  *(ushort *)(local_9c + 0x24) =
       *(ushort *)(local_9c + 0x24) & 0xfc3f | ((ushort)local_d4 & 0xf) << 6;
  if (param_3 != 0) {
    local_aa = (ushort)((*(uint *)(param_3 + 0x14) & 0x30) != 0);
    *(ushort *)(local_9c + 0x24) = *(ushort *)(local_9c + 0x24) & 0xffef | local_aa << 4;
    local_c4 = FUN_00479f30(param_3);
    if (local_c4 != 0) {
      local_9d = FUN_004b9830();
      *(ushort *)(local_9c + 0x24) = *(ushort *)(local_9c + 0x24) & 0xffdf | (local_9d & 1) << 5;
    }
  }
  *(ushort *)(local_9c + 0x24) =
       *(ushort *)(local_9c + 0x24) & 0xfff0 | *(ushort *)(*(int *)(local_9c + 8) + 0x58) & 0xf;
  *(undefined4 *)(local_9c + 0x28) = *(undefined4 *)(*(int *)(local_9c + 8) + 0x54);
  *(undefined4 *)(local_9c + 0x2c) = *(undefined4 *)(*(int *)(local_9c + 8) + 0x5c);
  *(float *)(local_9c + 0x30) =
       (*(float *)(local_9c + 0x2c) * *(float *)(*(int *)(local_9c + 8) + 0x38)) /
       (float)*(int *)(*(int *)(local_9c + 8) + 0x34);
  FUN_0062cf50();
  if (0.0 < *(float *)(*(int *)(local_9c + 8) + 0x50)) {
    local_c0 = *(float *)(*(int *)(local_9c + 8) + 0x50) * *(float *)(*(int *)(local_9c + 8) + 0x50)
    ;
    local_c8 = *(float *)(*(int *)(local_9c + 8) + 0x3c) * *(float *)(*(int *)(local_9c + 8) + 0x3c)
    ;
    iVar4 = *(int *)(local_9c + 0xc);
    local_98 = *(float *)(iVar4 + 0xa0);
    local_94 = *(undefined4 *)(iVar4 + 0xa4);
    local_90 = *(float *)(iVar4 + 0xa8);
    FUN_00820180();
    FUN_005b28e0((double)local_98,(double)local_90,(double)*(float *)(*(int *)(local_9c + 8) + 0x50)
                 ,local_144);
    while (cVar1 = FUN_00462710(&local_e0), cVar1 != '\0') {
      local_a4 = FUN_004da060(*local_e0);
      if (local_a4 != 0) {
        puVar2 = (undefined4 *)
                 (**(code **)(*(int *)(local_a4 + 0x18) + 0xc))(local_98,local_94,local_90);
        pfVar3 = (float *)FUN_004401a0(local_10c,*puVar2,puVar2[1]);
        local_38 = *pfVar3;
        local_34 = pfVar3[1];
        local_30 = pfVar3[2];
        local_b4 = local_38 * local_38 + local_34 * local_34 + local_30 * local_30;
        local_14 = local_38;
        local_10 = local_34;
        local_c = local_30;
        if (local_c8 <= local_b4) {
          if (local_b4 < local_c0) {
            local_dc = (local_c0 - local_b4) / (local_c0 - local_c8);
            local_fc = *(undefined4 *)(local_9c + 0x1c);
            local_f8 = *(undefined4 *)(local_9c + 0x20);
            local_f4 = *(undefined4 *)(local_9c + 0x24);
            local_f0 = *(float *)(local_9c + 0x28) * local_dc;
            (**(code **)(*(int *)(local_a4 + 0x18) + 0x38))();
          }
        }
        else {
          (**(code **)(*(int *)(local_a4 + 0x18) + 0x38))();
        }
      }
    }
  }
  if (*(int *)(*(int *)(local_9c + 8) + 100) != 0) {
    (**(code **)(**(int **)(*(int *)(local_9c + 8) + 100) + 8))();
  }
  for (local_a8 = 0; local_a8 < *(int *)(*(int *)(local_9c + 8) + 0x68); local_a8 = local_a8 + 1) {
    local_e8 = *(undefined4 *)(*(int *)(local_9c + 8) + 0x22c + local_a8 * 4);
    local_ec = *(int *)(*(int *)(local_9c + 8) + 0x6c + local_a8 * 4);
    local_b8 = (float *)(*(int *)(local_9c + 8) + 0xac + local_a8 * 0xc);
    local_b0 = (float *)(*(int *)(local_9c + 8) + 0x16c + local_a8 * 0xc);
    for (local_bc = 0; local_bc < local_ec; local_bc = local_bc + 1) {
      fVar5 = (float10)FUN_004464c0();
      local_cc = (float)fVar5;
      local_20 = local_cc * *local_b8 + *local_b0;
      fVar5 = (float10)FUN_004464c0();
      local_d8 = (float)fVar5;
      local_1c = local_d8 * local_b8[1] + local_b0[1];
      fVar5 = (float10)FUN_004464c0();
      local_d0 = (float)fVar5;
      local_18 = local_d0 * local_b8[2] + local_b0[2];
      pfVar3 = (float *)FUN_00440210(local_118,&local_20,*(int *)(local_9c + 0xc) + 0x20);
      local_2c = *pfVar3;
      local_28 = pfVar3[1];
      local_24 = pfVar3[2];
      local_44 = 0;
      local_40 = 0;
      local_3c = 0;
      local_20 = local_2c;
      local_1c = local_28;
      local_18 = local_24;
      FUN_004513e0();
    }
  }
  local_e4 = local_9c;
  FUN_00438b80(&local_e4);
  puVar2 = (undefined4 *)FUN_0042d8c0(local_100);
  *(undefined4 *)(local_9c + 4) = *puVar2;
  FUN_0083e885();
  return;
}

