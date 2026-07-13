
void __fastcall FUN_00596520(int *param_1)

{
  undefined1 local_108 [4];
  undefined1 local_104 [4];
  undefined1 local_100 [4];
  undefined1 local_fc [4];
  float local_f8;
  undefined4 local_f4;
  int local_f0;
  int local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  float local_d4;
  float local_d0;
  int local_cc;
  float local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int *local_8c;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_8c = param_1;
  if (DAT_00920f04 != 0) {
    if (param_1[0x21] < 0) {
      local_c0 = 2;
    }
    else {
      local_c0 = param_1[0x21];
    }
    local_cc = local_c0;
    local_90 = *(int *)(DAT_00920f04 + local_c0 * 4);
    if (local_90 != 0) {
      local_bc = *(int *)(local_90 + 0x78);
      local_b4 = *(int *)(local_90 + 0x7c);
      for (local_a0 = 0; local_a0 < local_bc; local_a0 = local_a0 + 1) {
        for (local_9c = 0; local_9c < local_b4; local_9c = local_9c + 1) {
          local_ec = *(int *)(*(int *)(*(int *)(local_90 + 0x80) + local_a0 * 4) + local_9c * 4);
          local_c4 = (int)*(float *)(local_ec + 0x1c);
          if (-100000 < local_c4) {
            local_ac = (float)local_9c * 80.0 + (float)DAT_00931018 * 5.0;
            local_a4 = (float)local_a0 * 80.0 + (float)DAT_00931020 * 5.0;
            local_d4 = local_ac + 80.0;
            local_f8 = local_a4 + 80.0;
            (**(code **)(*local_8c + 0x24))(local_ac,local_a4,&local_e4,&local_f4);
            (**(code **)(*local_8c + 0x24))(local_d4,local_f8,&local_dc,&local_e8);
            FUN_0068b020(DAT_00917580,local_e4,local_e8,local_dc,local_f4,DAT_00917584,0);
          }
        }
      }
      for (local_98 = 0; local_98 < local_bc; local_98 = local_98 + 1) {
        for (local_94 = 0; local_94 < local_b4; local_94 = local_94 + 1) {
          local_f0 = *(int *)(*(int *)(*(int *)(local_90 + 0x80) + local_98 * 4) + local_94 * 4);
          local_b8 = (int)*(float *)(local_f0 + 0x1c);
          if (-100000 < local_b8) {
            local_b0 = (float)local_94 * 80.0 + (float)DAT_00931018 * 5.0;
            local_a8 = (float)local_98 * 80.0 + (float)DAT_00931020 * 5.0;
            local_d0 = local_b0 + 80.0;
            local_c8 = local_a8 + 80.0;
            (**(code **)(*local_8c + 0x24))(local_b0,local_a8,&local_e0,local_fc);
            (**(code **)(*local_8c + 0x24))(local_d0,local_c8,local_108,&local_d8);
            sprintf(local_88," %ld",local_b8);
            FUN_004c0100(DAT_00917580,local_e0,local_d8,local_100,local_104,local_88,DAT_00917550,
                         DAT_0091755c,0xffffffff,0,0,0);
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

