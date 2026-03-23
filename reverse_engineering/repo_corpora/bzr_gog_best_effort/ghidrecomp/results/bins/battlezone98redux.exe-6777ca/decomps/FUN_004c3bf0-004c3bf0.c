
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004c3bf0(CDialog *param_1,undefined4 *param_2)

{
  ushort uVar1;
  float10 fVar2;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  float local_38;
  int local_34;
  int local_30;
  int local_2c;
  DLGTEMPLATE *local_28;
  int local_24;
  CWnd *local_20;
  void *local_1c;
  ushort *local_18;
  CDialog *local_14;
  ushort local_10;
  ushort local_c;
  char local_5;
  
  if ((DAT_00919850 == '\0') && (DAT_00919851 == '\0')) {
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  else {
    local_14 = param_1;
    FUN_00783540(&local_44);
    local_18 = (ushort *)FUN_004c0fe0(local_44);
    FUN_004c6ee0();
    local_28 = (DLGTEMPLATE *)FUN_00492d60(local_20);
    local_3c = *(int *)(**(int **)(local_14 + 0xc) + 0xc + *(int *)(local_14 + 0x10) * 0x24);
    if (DAT_00919851 == '\0') {
      local_30 = 1;
    }
    else {
      local_30 = -1;
    }
    local_24 = local_30;
    local_5 = '\0';
    if (((DAT_00919850 == '\0') || (*(int *)(local_14 + 0x18) != 0)) &&
       ((DAT_00919851 == '\0' || (*(int *)(local_14 + 0x1c) != 0)))) {
      if (((DAT_00919850 != '\0') && (*(int *)(local_14 + 0x18) == 1)) ||
         ((DAT_00919851 != '\0' && (*(int *)(local_14 + 0x1c) == 1)))) {
        local_2c = local_3c + -4;
        switch(local_3c) {
        case 4:
          if (DAT_00919853 == '\0') {
            if ((*(int *)(local_14 + 0x30) != -1) &&
               ((*local_18 & 0xff80) != (*(uint *)(local_14 + 0x30) & 0xff80))) {
              FUN_004c7250();
              uVar1 = FUN_004c7700();
              *local_18 = uVar1;
              local_5 = '\x01';
            }
          }
          else {
            local_10 = FUN_004c77a0(local_44,local_40);
            if ((*local_18 & 0xff80) != (local_10 & 0xff80)) {
              FUN_004c7250();
              *local_18 = local_10;
              local_5 = '\x01';
            }
          }
          break;
        case 10:
        case 0xc:
          FUN_004c1130(local_28,local_20,local_1c,local_30);
          break;
        case 0xb:
          CDialog::CreateIndirect(local_14,local_28,local_20,local_1c);
          break;
        case 0x10:
          FUN_004c1160(local_28,local_20,local_1c,local_30);
          break;
        case 0x15:
          CDialog::CreateIndirect(local_14,local_28,local_20,local_1c);
        }
      }
    }
    else {
      local_34 = local_3c;
      switch(local_3c) {
      case 0:
        if (DAT_009454ac == 0) {
          *(uint *)(local_14 + 0x30) = (uint)*local_18;
        }
        else {
          *(uint *)(local_14 + 0x34) = *(ushort *)local_28 & 0xfff;
          *(float *)(local_14 + 0xf4) = (float)*(int *)(local_14 + 0x34) * 0.1;
        }
        break;
      case 1:
        FUN_004c7250();
        if (local_24 < 1) {
          *local_18 = *local_18 & 0xff0f |
                      (ushort)(*(int *)(&DAT_008e8418 + ((int)(*local_18 & 0xf0) >> 4) * 4) << 4);
        }
        else {
          *local_18 = *local_18 & 0xff0f |
                      (ushort)(*(int *)(&DAT_008e8140 + ((int)(*local_18 & 0xf0) >> 4) * 4) << 4);
        }
        local_5 = '\x01';
        break;
      case 2:
        FUN_004c7250();
        *local_18 = *local_18 & 0xff0f |
                    (ushort)(*(int *)(&DAT_008e81a0 + ((int)(*local_18 & 0xf0) >> 4) * 4) << 4);
        local_5 = '\x01';
        break;
      case 3:
        FUN_004c7250();
        *local_18 = *local_18 & 0xff0f |
                    (ushort)(*(int *)(&DAT_008e85c0 + ((int)(*local_18 & 0xf0) >> 4) * 4) << 4);
        local_5 = '\x01';
        break;
      case 4:
        if (DAT_00919853 == '\0') {
          if (*(int *)(local_14 + 0x30) != -1) {
            FUN_004c7250();
            uVar1 = FUN_004c7700();
            *local_18 = uVar1;
          }
        }
        else {
          local_c = FUN_004c77a0(local_44,local_40);
          if ((*local_18 & 0xff80) != (local_c & 0xff80)) {
            FUN_004c7250();
            *local_18 = local_c;
          }
        }
        local_5 = '\x01';
        break;
      case 5:
        if (local_30 < 1) {
          local_38 = 0.5;
        }
        else {
          local_38 = 2.0;
        }
        *(float *)(local_14 + 0x44) = *(float *)(local_14 + 0x44) * local_38;
        fVar2 = (float10)FUN_00447ed0();
        *(float *)(local_14 + 0x44) = (float)fVar2;
        *(undefined4 *)(local_14 + 0x48) = *param_2;
        *(undefined4 *)(local_14 + 0x50) = param_2[2];
        fVar2 = (float10)FUN_007855e0((double)*(float *)(local_14 + 0x48),
                                      (double)*(float *)(local_14 + 0x50));
        *(float *)(local_14 + 0x4c) = (float)fVar2;
        break;
      case 6:
        FUN_004c7250();
        FUN_00782ef0(local_18,local_24);
        local_5 = '\x01';
        break;
      case 7:
        FUN_004c7250();
        FUN_00782fc0(local_18,local_24);
        local_5 = '\x01';
        break;
      case 8:
        FUN_004c7250();
        FUN_007830e0(local_18,local_24);
        local_5 = '\x01';
        break;
      case 9:
        FUN_004c7250();
        FUN_00783200(local_18,local_24);
        local_5 = '\x01';
        break;
      case 10:
      case 0xc:
        FUN_004c4700(local_28,local_20,local_1c,local_30,1);
        break;
      case 0xb:
        FUN_004c4560(local_28,local_20,local_1c,1);
        break;
      case 0x10:
        FUN_004c4bc0(local_28,local_20,local_1c,local_30,1);
        break;
      case 0x11:
        FUN_004c49a0(local_28,local_20,local_1c,local_30,1);
        break;
      case 0x15:
        FUN_004c4e10(local_28,local_20,local_1c,1);
      }
    }
    if (local_5 != '\0') {
      FUN_007777f0(local_20,local_1c,local_20 + 4,(int)local_1c + 4);
      FUN_004c1c50();
      _DAT_009454c0 = 1;
    }
    if (DAT_00919850 == '\0') {
      *(undefined4 *)(local_14 + 0x18) = 0;
    }
    else {
      *(undefined4 *)(local_14 + 0x18) = 1;
    }
    if (DAT_00919851 == '\0') {
      *(undefined4 *)(local_14 + 0x1c) = 0;
    }
    else {
      *(undefined4 *)(local_14 + 0x1c) = 1;
    }
  }
  return;
}

