
void __fastcall FUN_00587ef0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 local_120 [16];
  undefined1 local_110 [12];
  undefined1 local_104 [12];
  undefined1 local_f8 [12];
  undefined1 local_ec [12];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined4 local_c8;
  undefined8 local_c4;
  undefined8 local_bc;
  undefined8 local_b4;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
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
  
  iVar1 = DAT_008e80ac;
  iVar2 = DAT_008e80a4;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_80 = param_1;
  if (DAT_009454a4 == 0) {
    if (DAT_00915567 == '\0') {
      if ((DAT_008eaaac == 0) &&
         (iVar2 = FUN_0049f100(DAT_009175a0,DAT_009175a4,&DAT_009c83e8), iVar2 != 0)) {
        FUN_004a71e0(0,0);
        goto LAB_00588951;
      }
      local_90 = DAT_009175a0;
      local_8c = DAT_009175a4;
      local_88 = DAT_009175a0;
      local_84 = DAT_009175a4;
    }
    else {
      if (DAT_0097a268 == -32000) {
        if (DAT_008e80a8 == -32000) {
          if (DAT_008e80a0 == -32000) {
            local_88 = *(int *)(param_1 + 8);
            local_84 = *(int *)(param_1 + 0xc);
            local_90 = DAT_02cecf00 / 2;
            local_8c = DAT_02cecf04 / 2;
          }
          else {
            local_90 = DAT_008e80a0;
            local_8c = DAT_008e80a4;
            local_88 = DAT_008e80a0;
            local_84 = DAT_008e80a4;
            local_c4 = FUN_00497780(param_1 + 0x44,DAT_00917594,0);
            local_98 = (int)local_c4 - (local_88 - *(int *)(local_80 + 8));
            local_94 = (int)((ulonglong)local_c4 >> 0x20) - (local_84 - *(int *)(local_80 + 0xc));
            puVar4 = (undefined4 *)FUN_00587830(local_f8,local_98,local_94,DAT_00917594);
            local_e0 = *puVar4;
            local_60 = puVar4[1];
            local_dc = puVar4[2];
            local_64 = local_e0;
            local_5c = local_dc;
            local_24 = local_e0;
            local_20 = local_60;
            local_1c = local_dc;
            FUN_005889d0(local_e0,local_dc);
            FUN_0049f090();
            *(int *)(local_80 + 8) = local_88;
            *(int *)(local_80 + 0xc) = local_84;
          }
        }
        else {
          local_90 = DAT_008e80a8;
          local_8c = DAT_008e80ac;
          local_88 = DAT_008e80a8;
          local_84 = DAT_008e80ac;
          *(int *)(param_1 + 8) = DAT_008e80a8;
          *(int *)(param_1 + 0xc) = iVar1;
          FUN_0049f070();
          FUN_0049f090();
        }
      }
      else {
        local_90 = DAT_008e80a0;
        local_8c = DAT_008e80a4;
        local_88 = DAT_008e80a0;
        local_84 = DAT_008e80a4;
        *(int *)(param_1 + 8) = DAT_008e80a0;
        *(int *)(param_1 + 0xc) = iVar2;
        FUN_0049f0b0();
      }
      if (local_88 == -32000) goto LAB_00588951;
    }
    FUN_00587b90(local_90,local_8c);
    iVar2 = FUN_00451de0();
    if (iVar2 == 0) {
      uVar3 = FUN_005879e0(local_88,local_84);
      *(undefined4 *)(local_80 + 0x30) = uVar3;
      puVar4 = (undefined4 *)FUN_00587830(local_110,local_88,local_84,DAT_00917594);
      local_58 = *puVar4;
      local_54 = puVar4[1];
      local_50 = puVar4[2];
      *(undefined4 *)(local_80 + 0x24) = local_58;
      *(undefined4 *)(local_80 + 0x28) = local_54;
      *(undefined4 *)(local_80 + 0x2c) = local_50;
      DAT_025ce778 = local_80 + 0x24;
      if (*(int *)(local_80 + 0x10) == 0) {
        if (*(int *)(local_80 + 0x30) == 0) {
          if ((((*(float *)(local_80 + 0x24) <= DAT_0091738c) ||
               (DAT_00917394 < *(float *)(local_80 + 0x24) ||
                DAT_00917394 == *(float *)(local_80 + 0x24))) ||
              (*(float *)(local_80 + 0x2c) <= DAT_00917390)) ||
             (DAT_00917388 < *(float *)(local_80 + 0x2c) ||
              DAT_00917388 == *(float *)(local_80 + 0x2c))) {
            *(undefined4 *)(local_80 + 0x14) = 0;
            FUN_004a71e0(*(undefined4 *)(local_80 + 0x14),local_80 + 0x24);
          }
          else {
            uVar3 = FUN_0045bd80(local_80 + 0x24);
            *(undefined4 *)(local_80 + 0x14) = uVar3;
            FUN_004a71e0(*(undefined4 *)(local_80 + 0x14),local_80 + 0x24);
          }
        }
        else {
          uVar3 = FUN_0045bbe0(*(undefined4 *)(local_80 + 0x30));
          *(undefined4 *)(local_80 + 0x14) = uVar3;
          FUN_004a7230(*(undefined4 *)(local_80 + 0x14),*(undefined4 *)(local_80 + 0x30));
        }
      }
      if (DAT_00919871 == '\0') {
        local_9c = *(int *)(local_80 + 0x10) + *(int *)(local_80 + 0x10) + (int)DAT_00919872;
        if (local_9c == 1) {
          *(undefined4 *)(local_80 + 0x18) = *(undefined4 *)(local_80 + 0x24);
          *(undefined4 *)(local_80 + 0x1c) = *(undefined4 *)(local_80 + 0x28);
          *(undefined4 *)(local_80 + 0x20) = *(undefined4 *)(local_80 + 0x2c);
          local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
          local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
          if (*(int *)(local_80 + 0x14) == 1) {
            local_ac = FUN_0045bba0();
            if ((local_ac < 0x23) || (0x2c < local_ac)) {
              if (DAT_00919875 == '\0') {
                FUN_004a6cd0(*(undefined4 *)(local_80 + 0x30));
                local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
                local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
              }
              else {
                FUN_004a6c70(*(undefined4 *)(local_80 + 0x30));
                local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
                local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
              }
            }
            else {
              local_a8 = FUN_00417c70();
              local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
              local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
              if (local_a8 != 0) {
                FUN_0049f450(*(undefined4 *)(local_80 + 0x30));
                local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
                local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
              }
            }
          }
        }
        else if (local_9c == 2) {
          local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
          local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
          if (*(int *)(local_80 + 0x14) != 0) {
            if (*(int *)(local_80 + 0x30) == 0) {
              FUN_004a70c0(*(undefined4 *)(local_80 + 0x14),local_80 + 0x24);
            }
            else {
              FUN_004a7050(*(undefined4 *)(local_80 + 0x14),*(undefined4 *)(local_80 + 0x30));
            }
            local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
            local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
            if ((*(int *)(local_80 + 0x14) != 1) &&
               (local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc),
               local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4),
               *(int *)(local_80 + 0x14) != 9)) {
              FUN_004a6d50();
            }
          }
        }
        else if ((local_9c == 3) &&
                (local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc),
                local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4), DAT_00915567 == '\0')) {
          local_bc = FUN_00497780(local_80 + 0x18,DAT_00917594,0);
          local_b4 = local_bc;
          puVar4 = (undefined4 *)FUN_005872e0(local_120,local_bc,local_88,local_84);
          local_4c = *puVar4;
          local_48 = puVar4[1];
          local_44 = puVar4[2];
          local_40 = puVar4[3];
          local_18 = local_4c;
          local_14 = local_48;
          local_10 = local_44;
          local_c = local_40;
          iVar2 = FUN_00587360(&local_18);
          if (100 < iVar2) {
            FUN_00587780(local_18,local_14,local_10,local_c,DAT_0091755c);
            FUN_004a6b00(local_18,local_14,local_10,local_c);
            *(undefined4 *)(local_80 + 0x14) = 1;
          }
        }
      }
      else {
        FUN_004a6d50();
        local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
        local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
      }
      *(int *)(local_80 + 0x10) = (int)DAT_00919872;
      local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8);
      local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0);
    }
    else {
      if ((DAT_02cc3150 & 1) == 0) {
        DAT_02cc3150 = DAT_02cc3150 | 1;
        puVar4 = &DAT_008fe1e0;
        puVar5 = &DAT_02cc3110;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
      }
      uVar3 = FUN_005879e0(local_88,local_84);
      *(undefined4 *)(local_80 + 0x30) = uVar3;
      puVar4 = (undefined4 *)FUN_00587830(local_ec,local_88,local_84,DAT_00917594);
      local_30 = *puVar4;
      local_2c = puVar4[1];
      local_28 = puVar4[2];
      *(undefined4 *)(local_80 + 0x24) = local_30;
      *(undefined4 *)(local_80 + 0x28) = local_2c;
      *(undefined4 *)(local_80 + 0x2c) = local_28;
      DAT_025ce778 = local_80 + 0x24;
      if (*(int *)(local_80 + 0x30) == 0) {
        *(undefined4 *)(local_80 + 0x14) = 0;
      }
      else {
        *(undefined4 *)(local_80 + 0x14) = 1;
      }
      if (*(int *)(local_80 + 0x30) == 0) {
        FUN_004a71e0(*(undefined4 *)(local_80 + 0x14),local_80 + 0x24);
      }
      else {
        FUN_004a7230(*(undefined4 *)(local_80 + 0x14),*(undefined4 *)(local_80 + 0x30));
      }
      if (DAT_02cc2bd4 == 0) {
        if (((DAT_00919870 != '\0') ||
            (local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8),
            local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc),
            local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0),
            local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4), DAT_00919871 != '\0')) &&
           (DAT_02cc2bd4 = *(int *)(local_80 + 0x30),
           local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8),
           local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc),
           local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0),
           local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4), DAT_02cc2bd4 != 0)) {
          puVar4 = (undefined4 *)FUN_0045c4d0();
          puVar5 = &DAT_02cc3110;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
        }
      }
      else if (DAT_00919874 == '\0') {
        if ((DAT_00919872 == '\0') || (DAT_00919873 == '\0')) {
          if (DAT_00919872 == '\0') {
            if (DAT_00919873 == '\0') {
              DAT_02cc2bd4 = 0;
              local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8);
              local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
              local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0);
              local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
            }
            else {
              FUN_004c0af0(&local_7c);
              puVar4 = (undefined4 *)
                       FUN_004401a0(local_104,*(undefined4 *)(local_80 + 0x24),
                                    *(undefined4 *)(local_80 + 0x28),
                                    *(undefined4 *)(local_80 + 0x2c),local_7c,local_78,local_74);
              local_70 = *puVar4;
              local_6c = puVar4[1];
              local_68 = puVar4[2];
              local_3c = local_70;
              local_38 = local_6c;
              local_34 = local_68;
              FUN_00587400(&local_70);
              local_d8 = FUN_00497780(&local_7c,DAT_00917594,0);
              local_d0 = local_d8;
              FUN_0068af40(DAT_00917580,local_d8,local_88,local_84,DAT_0091755c,0);
              local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
              local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
            }
          }
          else {
            FUN_005873a0(local_80 + 0x24);
            local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8);
            local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
            local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0);
            local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
          }
        }
        else {
          FUN_0056d6a0(&DAT_02cc3110);
          DAT_02cc2bd4 = 0;
          local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8);
          local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
          local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0);
          local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
        }
      }
      else {
        (**(code **)(*(int *)(DAT_02cc2bd4 + 0x18) + 0x10))();
        DAT_02cc2bd4 = 0;
        local_d8 = CONCAT44(local_d8._4_4_,(undefined4)local_d8);
        local_bc = CONCAT44(local_bc._4_4_,(undefined4)local_bc);
        local_d0 = CONCAT44(local_d0._4_4_,(undefined4)local_d0);
        local_b4 = CONCAT44(local_b4._4_4_,(undefined4)local_b4);
      }
    }
    if (DAT_00919876 != '\0') {
      local_a4 = FUN_00417c70();
      if (local_a4 != 0) {
        FUN_00588970(local_a4);
      }
    }
    if (DAT_00919877 != '\0') {
      local_c8 = FUN_00462370();
      local_a0 = FUN_005e0f70(1);
      if (local_a0 != 0) {
        FUN_00588970(local_a0);
      }
    }
    FUN_0050cda0(*(undefined4 *)(&DAT_008e8d1c + *(int *)(local_80 + 0x14) * 8));
  }
LAB_00588951:
  FUN_0083e885();
  return;
}

