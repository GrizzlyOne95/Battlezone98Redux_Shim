
void __thiscall FUN_0046ffc0(int param_1,float param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined1 local_f4 [12];
  undefined1 local_e8 [12];
  undefined1 local_dc [4];
  float local_d8;
  float local_d4;
  undefined4 local_d0;
  float local_cc;
  float local_c8;
  undefined4 local_c4;
  int local_c0;
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  uint local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  undefined1 local_a0 [4];
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  char local_8a;
  char local_89;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78 [16];
  undefined1 local_38 [12];
  float local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c4 = *(undefined4 *)(param_1 + 0x228);
  local_88 = param_1;
  switch(local_c4) {
  case 0:
    if (*(int *)(*(int *)(param_1 + 0x230) + 0xe0) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xe0) = 0;
      if (*(int *)(param_1 + 0x300) < 1) {
        local_89 = '\0';
      }
      else if (*(int *)(param_1 + 0xac) == 4) {
        iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0xb0));
        local_89 = iVar5 != 0;
        local_b0 = (uint)(byte)local_89;
      }
      else {
        local_94 = FUN_00462610();
        if (local_94 == 0) {
          local_89 = '\0';
          local_b8 = DAT_00917a74;
          FID_conflict_begin(local_a0);
          while( true ) {
            uVar3 = FID_conflict_end(local_dc);
            cVar1 = FID_conflict_operator__(uVar3);
            if (cVar1 == '\0') break;
            piVar2 = (int *)FUN_00421ec0();
            local_98 = *piVar2;
            uVar3 = (**(code **)(*(int *)(local_98 + 0x18) + 4))();
            cVar1 = FUN_004db600(uVar3);
            if (cVar1 != '\0') {
              uVar3 = FUN_004625b0();
              cVar1 = FUN_004db600(uVar3);
              if (cVar1 != '\0') {
                puVar4 = (undefined4 *)(**(code **)(*(int *)(local_98 + 0x18) + 0xc))();
                fVar7 = (float10)FUN_004620b0(*(undefined4 *)(local_88 + 0x108),
                                              *(undefined4 *)(local_88 + 0x10c),
                                              *(undefined4 *)(local_88 + 0x110),*puVar4,puVar4[1],
                                              puVar4[2]);
                local_c8 = (float)fVar7;
                if (local_c8 < 5625.0) {
                  local_89 = '\x01';
                  break;
                }
              }
            }
            FUN_00421ee0();
          }
        }
        else {
          uVar3 = (**(code **)(*(int *)(local_94 + 0x18) + 4))();
          cVar1 = FUN_004db600(uVar3);
          if (cVar1 == '\0') {
LAB_00470191:
            local_b4 = 0;
          }
          else {
            uVar3 = FUN_004625b0();
            cVar1 = FUN_004db600(uVar3);
            if (cVar1 == '\0') goto LAB_00470191;
            puVar4 = (undefined4 *)(**(code **)(*(int *)(local_94 + 0x18) + 0xc))();
            puVar4 = (undefined4 *)
                     (**(code **)(*(int *)(local_88 + 0x18) + 0xc))(*puVar4,puVar4[1],puVar4[2]);
            fVar7 = (float10)FUN_004620b0(*puVar4,puVar4[1],puVar4[2]);
            local_d4 = (float)fVar7;
            if (5625.0 <= local_d4) goto LAB_00470191;
            local_b4 = 1;
          }
          local_89 = (char)local_b4;
        }
      }
      if (local_89 == '\0') {
        FUN_004376c0("mnu_buzz.wav",*(undefined4 *)(local_88 + 0xf4),0);
      }
      else {
        *(undefined4 *)(local_88 + 0x228) = 1;
        FUN_004376c0(*(int *)(local_88 + 0xf8) + 0x5d0,*(undefined4 *)(local_88 + 0xf4),0);
      }
    }
    if ((*(int *)(local_88 + 0x300) < *(int *)(*(int *)(local_88 + 0xf8) + 0x5fc)) &&
       (*(float *)(local_88 + 0x308) = *(float *)(local_88 + 0x308) - param_2,
       *(float *)(local_88 + 0x308) <= 0.0)) {
      local_bc = *(float *)(*(int *)(local_88 + 0xf8) + 0x604) *
                 *(float *)(*(int *)(local_88 + 0xf8) + 0x604);
      local_8a = '\0';
      local_a4 = FUN_005e0f70(1);
      if (local_a4 != 0) {
        puVar4 = (undefined4 *)(**(code **)(*(int *)(local_a4 + 0x18) + 0xc))();
        puVar4 = (undefined4 *)
                 (**(code **)(*(int *)(local_88 + 0x18) + 0xc))(*puVar4,puVar4[1],puVar4[2]);
        fVar7 = (float10)FUN_004620b0(*puVar4,puVar4[1],puVar4[2]);
        local_d8 = (float)fVar7;
        if (local_d8 < local_bc) {
          local_8a = '\x01';
        }
      }
      if (local_8a == '\0') {
        for (local_9c = 0x4b; local_9c < 0x50; local_9c = local_9c + 1) {
          local_a8 = FUN_005e0f70(local_9c);
          if (local_a8 != 0) {
            puVar4 = (undefined4 *)(**(code **)(*(int *)(local_a8 + 0x18) + 0xc))();
            puVar4 = (undefined4 *)
                     (**(code **)(*(int *)(local_88 + 0x18) + 0xc))(*puVar4,puVar4[1],puVar4[2]);
            fVar7 = (float10)FUN_004620b0(*puVar4,puVar4[1],puVar4[2]);
            local_cc = (float)fVar7;
            if (local_cc < local_bc) {
              local_8a = '\x01';
              break;
            }
          }
        }
      }
      if (local_8a == '\0') {
        *(undefined4 *)(local_88 + 0x308) = 0x3e4ccccd;
      }
      else {
        *(int *)(local_88 + 0x300) = *(int *)(local_88 + 0x300) + 1;
        if (*(int *)(local_88 + 0x300) < *(int *)(*(int *)(local_88 + 0xf8) + 0x5fc)) {
          *(float *)(local_88 + 0x308) =
               *(float *)(local_88 + 0x308) + *(float *)(*(int *)(local_88 + 0xf8) + 0x608);
        }
        else {
          *(undefined4 *)(local_88 + 0x308) = 0;
        }
      }
    }
    break;
  case 1:
    if (0 < *(int *)(param_1 + 0x300)) {
      *(float *)(param_1 + 0x304) = *(float *)(param_1 + 0x304) - param_2;
      if (*(float *)(param_1 + 0x304) <= 0.0) {
        *(float *)(param_1 + 0x304) =
             *(float *)(param_1 + 0x304) + *(float *)(*(int *)(param_1 + 0xf8) + 0x600);
        cVar1 = FUN_004b9830();
        if (cVar1 == '\0') {
          local_d0 = *(undefined4 *)(*(int *)(local_88 + 0xf8) + 0x5f8);
          local_2c = (*(float *)(*(int *)(local_88 + 0xf4) + 0xb0) +
                     *(float *)(*(int *)(local_88 + 0xf4) + 0xbc)) * 0.5;
          local_28 = (*(float *)(*(int *)(local_88 + 0xf4) + 0xb4) +
                     *(float *)(*(int *)(local_88 + 0xf4) + 0xc0)) * 0.5;
          local_24 = *(undefined4 *)(*(int *)(local_88 + 0xf4) + 0xb8);
          FUN_00820180(local_38,&local_2c,1,*(int *)(local_88 + 0xf4) + 0x20);
          puVar4 = (undefined4 *)(*(int *)(local_88 + 0xf4) + 0x20);
          puVar6 = local_78;
          for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          FUN_00462160(local_78,local_38);
          uVar10 = 0;
          uVar9 = 0xffffffff;
          uVar8 = 0;
          uVar3 = (**(code **)(*(int *)(local_88 + 0x18) + 4))(0,0xffffffff,0);
          local_90 = FUN_004e1190(local_78,uVar3,uVar8,uVar9,uVar10);
          if (local_90 != 0) {
            iVar5 = FUN_00572a70();
            if (iVar5 != 0) {
              FUN_004b8460();
            }
            local_84 = 0;
            local_80 = 0x40a00000;
            local_7c = 0x40a00000;
            puVar4 = (undefined4 *)FUN_00440210(local_f4,&local_84,*(int *)(local_88 + 0xf4) + 0x20)
            ;
            local_84 = *puVar4;
            local_80 = puVar4[1];
            local_7c = puVar4[2];
            local_14 = local_84;
            local_10 = local_80;
            local_c = local_7c;
            puVar4 = (undefined4 *)
                     FUN_00440130(local_e8,*(undefined4 *)(local_88 + 300),
                                  *(undefined4 *)(local_88 + 0x130),
                                  *(undefined4 *)(local_88 + 0x134),local_84,local_80,local_7c);
            local_20 = *puVar4;
            local_1c = puVar4[1];
            local_18 = puVar4[2];
            FUN_0046fb20(&local_20);
            uVar3 = FUN_0045ca50(local_90);
            FUN_00461440(uVar3);
            if (*(int *)(local_88 + 0xac) == 4) {
              local_ac = FUN_00462630(*(undefined4 *)(local_88 + 0xb0));
              if (local_ac != 0) {
                FUN_004dbd60(4,local_ac);
              }
            }
            else {
              local_c0 = FUN_00462610();
              if (local_c0 != 0) {
                FUN_004dbd60(4,local_c0);
              }
            }
            FUN_0046fc40(local_88);
          }
        }
        *(int *)(local_88 + 0x300) = *(int *)(local_88 + 0x300) + -1;
      }
      break;
    }
    *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x60c);
    *(undefined4 *)(param_1 + 0x228) = 2;
    *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xe0) = 1;
    if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x30) == 0) break;
  case 2:
    if (*(int *)(*(int *)(param_1 + 0x230) + 0xe0) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xe0) = 0;
      *(undefined4 *)(param_1 + 0x228) = 3;
      FUN_004376c0(*(int *)(param_1 + 0xf8) + 0x5e0,*(undefined4 *)(param_1 + 0xf4),0);
    }
    break;
  case 3:
    *(undefined4 *)(param_1 + 0x228) = 0;
  }
  FUN_004ebfd0(param_2);
  FUN_0083e885();
  return;
}

