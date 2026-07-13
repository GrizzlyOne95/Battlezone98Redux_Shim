
void __fastcall FUN_00418fb0(int *param_1)

{
  float fVar1;
  float fVar2;
  char cVar3;
  char *pcVar4;
  ulong local_70;
  undefined8 local_6c;
  ulong local_64;
  int local_60;
  int local_5c;
  float local_58;
  float local_54;
  float local_50;
  undefined8 local_4c;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined1 *local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  float local_1c;
  float local_18;
  int local_14;
  int local_10;
  float local_c;
  int *local_8;
  
  fVar2 = DAT_00920ef4;
  if ((param_1[0x1b] != 0) &&
     (local_8 = param_1, cVar3 = (**(code **)(*param_1 + 0x14))(), fVar2 = DAT_00920ef4,
     cVar3 != '\0')) {
    if (local_8[2] == 0) {
      FUN_00417990(local_8[0x1d]);
    }
    else {
      FUN_00417990(local_8[0x1e]);
    }
    local_20 = (local_8[9] - local_8[7]) + 1;
    local_28 = (local_8[10] - local_8[8]) + 1;
    FUN_0068ca30(DAT_00917580,DAT_009469c8,local_8[0x1b],local_8[7] + local_8[0x15],
                 local_8[8] + local_8[0x16],local_20,local_28,5,0);
    fVar2 = DAT_00920ef4;
    if (local_8[0x18] == 0) {
      if (((char)local_8[0x17] != '\0') &&
         (cVar3 = FUN_005dbf50(&local_34,&local_70,&local_5c,&local_24,&local_64,&local_60),
         fVar2 = DAT_00920ef4, cVar3 != '\0')) {
        DAT_00920ef4 = DAT_00920ef4 - 0.001;
        local_1c = 0.0;
        local_18 = 0.0;
        local_c = 0.0;
        FUN_00689ab0(DAT_0091552c,&DAT_008711c0,&local_c,&local_18);
        fVar1 = local_c;
        if (local_5c == 0) {
          local_c = 0.0;
        }
        if (local_34 == (undefined1 *)0x0) {
          local_34 = &DAT_008a1ad8;
        }
        FUN_00689ab0(DAT_0091552c,local_34,&local_1c,&local_18);
        local_44 = 0.85;
        local_40 = 1.0;
        if ((float)local_20 * 0.85 < local_1c + local_c) {
          local_40 = ((float)local_20 * 0.85) / (local_1c + local_c);
          local_4c = FUN_00689eb0();
          FUN_00689ec0((float)local_4c * local_40,(float)((ulonglong)local_4c >> 0x20) * local_40);
          FUN_00689ab0(DAT_0091552c,local_34,&local_1c,&local_18);
          if (local_c != 0.0) {
            FUN_00689ab0(DAT_0091552c,&DAT_008711c0,&local_c,&local_18);
          }
        }
        local_14 = (int)((float)(int)((float)(local_8[7] + local_8[0x15]) + (float)local_20 / 2.0) -
                        (local_1c + local_c) / 2.0);
        local_10 = local_8[8] + local_8[0x16];
        if (local_8[0x1a] == 2) {
          local_10 = (int)((float)local_10 - local_18);
          if (local_24 != 0) {
            local_10 = (int)((float)local_10 - local_18);
          }
        }
        else if (local_8[0x1a] == 1) {
          local_10 = local_10 + local_28;
          if (local_24 != 0) {
            local_10 = (int)((float)local_10 + local_18);
          }
        }
        else {
          local_10 = (int)((float)(local_10 + local_28) - ((float)(local_28 / 2) + local_18 / 2.0));
          if (local_24 != 0) {
            local_10 = (int)((float)local_10 - local_18 * 0.5);
          }
        }
        if (local_5c != 0) {
          FUN_00417990(local_70);
          FUN_0068c560(DAT_00917580,local_5c,local_14,local_10,5,0);
        }
        std::_Init_atomic_counter(DAT_0091552c,local_70);
        FUN_00689d10(DAT_0091552c,DAT_00917580,(int)((float)local_14 + local_c),local_10,local_34);
        if (local_40 != 1.0) {
          FUN_00689ec0(local_4c);
        }
        if (local_24 != 0) {
          local_10 = (int)((float)local_10 + local_18);
          local_3c = 1.0;
          local_c = fVar1;
          if (local_60 == 0) {
            local_c = 0.0;
          }
          FUN_00689ab0(DAT_0091552c,local_24,&local_1c,&local_18);
          if ((float)local_20 * local_44 < local_1c + local_c) {
            local_3c = ((float)local_20 * local_44) / (local_1c + local_c);
            FUN_00689ec0((float)local_4c * local_3c,local_4c._4_4_ * local_3c);
            FUN_00689ab0(DAT_0091552c,local_24,&local_1c,&local_18);
            if (local_c != 0.0) {
              FUN_00689ab0(DAT_0091552c,&DAT_008711c0,&local_c,&local_18);
            }
          }
          local_14 = (int)((float)(int)((float)(local_8[7] + local_8[0x15]) + (float)local_20 / 2.0)
                          - (local_1c + local_c) / 2.0);
          if (local_60 != 0) {
            FUN_00417990(local_64);
            FUN_0068c560(DAT_00917580,local_60,local_14,local_10,5,0);
          }
          std::_Init_atomic_counter(DAT_0091552c,local_64);
          FUN_00689d10(DAT_0091552c,DAT_00917580,(int)((float)local_14 + local_c),local_10,local_24)
          ;
          if (local_3c != 1.0) {
            FUN_00689ec0(local_4c);
          }
        }
      }
    }
    else {
      DAT_00920ef4 = DAT_00920ef4 - 0.001;
      local_38 = 0.0;
      local_54 = 0.0;
      FUN_00689ab0(DAT_0091552c,local_8[0x18],&local_38,&local_54);
      local_58 = 0.7;
      pcVar4 = strchr((char *)local_8[0x18],10);
      if (pcVar4 != (char *)0x0) {
        local_58 = 0.5;
      }
      local_50 = 1.0;
      if ((float)local_20 * local_58 < local_38) {
        local_50 = ((float)local_20 * local_58) / local_38;
        local_6c = FUN_00689eb0();
        FUN_00689ec0((float)local_6c * local_50,(float)((ulonglong)local_6c >> 0x20) * local_50);
        FUN_00689ab0(DAT_0091552c,local_8[0x18],&local_38,&local_54);
      }
      local_30 = (int)((float)(int)((float)(local_8[7] + local_8[0x15]) + (float)local_20 / 2.0) -
                      local_38 / 2.0);
      local_2c = local_8[8] + local_8[0x16];
      if (local_8[0x1a] == 2) {
        local_2c = (int)((float)local_2c - local_54);
      }
      else if (local_8[0x1a] == 1) {
        local_2c = local_2c + local_28;
      }
      else {
        local_2c = (int)((float)(local_2c + local_28) - ((float)(local_28 / 2) + local_54 / 2.0));
      }
      std::_Init_atomic_counter(DAT_0091552c,DAT_0091755c);
      FUN_00689d10(DAT_0091552c,DAT_00917580,local_30,local_2c,local_8[0x18]);
      if (local_50 != 1.0) {
        FUN_00689ec0(local_6c);
      }
    }
  }
  DAT_00920ef4 = fVar2;
  return;
}

