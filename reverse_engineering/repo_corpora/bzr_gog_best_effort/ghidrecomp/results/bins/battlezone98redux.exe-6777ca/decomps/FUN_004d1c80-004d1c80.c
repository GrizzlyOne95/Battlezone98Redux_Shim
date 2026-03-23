
/* WARNING: Type propagation algorithm not settling */

void __thiscall FUN_004d1c80(int param_1,float *param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_134 [44];
  undefined1 local_108 [12];
  float local_fc;
  undefined4 *local_f8;
  int local_f4;
  int local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  float local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  float local_c4;
  int local_c0;
  int local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  float local_50;
  float local_4c;
  int local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c8 = param_1;
  if (((DAT_008eaad8 != 10) && (DAT_008eaad8 != 9)) && (*(int *)(param_1 + 0x28) != 0)) {
    if (*(char *)(param_1 + 0x2c) != '\0') {
      FUN_004d22f0();
      *(undefined1 *)(local_c8 + 0x2c) = 0;
    }
    local_cc = FUN_00417c70();
    if (local_cc != 0) {
      local_fc = param_2[0xe];
      local_ac = (float)*(double *)(param_2 + 0x58);
      local_a8 = (float)*(double *)(param_2 + 0x5a);
      local_a4 = (float)*(double *)(param_2 + 0x5c);
      local_a0 = 100.0;
      local_48[0] = 0;
      memset(local_48 + 1,0,0x3c);
      for (local_c0 = 1; local_c0 < 0x10; local_c0 = local_c0 + 1) {
        local_d0 = *(int *)(&DAT_009180e8 + local_c0 * 4);
        if (local_d0 != 0) {
          local_48[local_c0] = *(int *)(local_d0 + 0x50);
        }
      }
      FUN_005b28e0((double)local_ac,(double)local_a4,(double)local_a0,local_134);
      while (cVar1 = FUN_00462710(&local_f8), cVar1 != '\0') {
        local_bc = FUN_004da060(*local_f8);
        if (((local_bc != 0) && (local_bc != local_cc)) &&
           (uVar2 = FUN_0045c4b0(), (uVar2 & 0x600) == 0)) {
          iVar3 = (**(code **)(*(int *)(local_bc + 0x18) + 4))();
          local_d4 = local_48[iVar3];
          if ((0 < local_d4) &&
             (((iVar3 = (*(code *)**(undefined4 **)(local_bc + 0x18))(), *(int *)(iVar3 + 0x1c) == 1
               || (iVar3 = (*(code *)**(undefined4 **)(local_bc + 0x18))(),
                  *(int *)(iVar3 + 0x1c) == 6)) ||
              ((iVar3 = (*(code *)**(undefined4 **)(local_bc + 0x18))(), *(int *)(iVar3 + 0x1c) == 4
               || (iVar3 = (*(code *)**(undefined4 **)(local_bc + 0x18))(),
                  *(int *)(iVar3 + 0x1c) == 2)))))) {
            puVar4 = (undefined4 *)(**(code **)(*(int *)(local_bc + 0x18) + 0xc))();
            local_b8 = *puVar4;
            local_b4 = puVar4[1];
            local_b0 = puVar4[2];
            fVar5 = (float10)FUN_004620b0();
            local_e4 = (float)fVar5;
            if ((local_e4 <= local_a0 * local_a0) && (FUN_00820180(), 0.0001 <= local_4c)) {
              iVar3 = FUN_00462400();
              local_e8 = *(undefined4 *)(iVar3 + 0xc);
              iVar3 = FUN_006895d0(param_2,&local_54,local_e8);
              if (iVar3 < 1) {
                local_ec = 0x3f800000;
                puVar4 = (undefined4 *)FUN_0049c4f0();
                local_9c = *puVar4;
                local_98 = puVar4[1];
                local_94 = puVar4[2];
                local_90 = puVar4[3];
                local_8c = puVar4[4];
                local_88 = puVar4[5];
                local_84 = local_9c;
                local_80 = local_98;
                local_7c = local_94;
                local_78 = local_90;
                local_74 = local_8c;
                local_70 = local_88;
                puVar4 = (undefined4 *)
                         FUN_004401a0(local_108,local_b8,local_b4,local_b0,local_ac,local_a8,
                                      local_a4);
                local_6c = *puVar4;
                local_68 = puVar4[1];
                local_64 = puVar4[2];
                local_60 = local_6c;
                local_5c = local_68;
                local_58 = local_64;
                iVar3 = FUN_00784620(local_84,local_80,local_7c,local_78,local_74,local_70,local_6c,
                                     local_68,local_64,&local_ec,0);
                if (iVar3 == 0) {
                  local_c4 = 1.0 / local_4c;
                  local_e0 = (int)(param_2[2] * local_54 * local_c4 + *param_2);
                  local_d8 = (int)(param_2[3] * local_50 * local_c4 + param_2[1]);
                  iVar3 = FUN_00462400();
                  local_f4 = (int)(*(float *)(iVar3 + 0xc) * param_2[2] * local_c4);
                  local_f0 = (int)(param_2[2] * 2.0 * local_c4);
                  local_dc = (int)(param_2[3] * -1.0 * local_c4);
                  FUN_0068ce80(param_2,local_d4,local_e0,local_d8 - local_f4,local_4c,local_f0,
                               local_dc,0x290000);
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

