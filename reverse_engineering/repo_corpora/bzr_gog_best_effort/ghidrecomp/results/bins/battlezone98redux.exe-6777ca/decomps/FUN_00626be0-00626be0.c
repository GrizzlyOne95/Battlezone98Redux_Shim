
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00626be0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_84 [4];
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined4 local_6c;
  undefined4 local_68;
  void *local_64;
  int local_60;
  int local_5c;
  undefined1 local_58 [4];
  undefined4 local_54;
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  int local_48;
  int local_44;
  int local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  float local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined1 local_1c [4];
  float local_18;
  float local_14;
  short *local_10;
  short *local_c;
  float local_8;
  
  if ((DAT_0091815a == '\0') || (DAT_00917f4c == '\0')) {
    DAT_0092017c = 0;
    DAT_0091815a = '\0';
    for (local_48 = FUN_0056f950(); local_48 != 0; local_48 = FUN_00577b50(local_48)) {
      local_64 = operator_new(0x90);
      if (local_64 == (void *)0x0) {
        local_68 = 0;
      }
      else {
        local_68 = FUN_00626540(*(undefined2 *)(local_48 + 0x28));
      }
      local_6c = local_68;
    }
    FUN_00626900();
    local_40 = FUN_00462370();
    DAT_00920178 = 0;
    DAT_00920180 = 0;
    FUN_00422170();
    local_20 = 1;
    local_24 = 1;
    local_28 = 1;
    local_2c = 1;
    local_38 = 1;
    local_34 = 0;
    if (DAT_00920174 == 0) {
      if (DAT_00920170 == 0) {
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec78c,&local_30,local_58);
        if ((float)local_20 < (float)_DAT_008ec774 + local_30) {
          local_20 = (int)((float)_DAT_008ec774 + local_30);
        }
        FUN_00689ab0(DAT_0091552c,PTR_s_Player_008ec77c,&local_30,local_58);
        if ((float)local_24 < (float)_DAT_008ec774 + local_30) {
          local_24 = (int)((float)_DAT_008ec774 + local_30);
        }
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec724,&local_30,local_58);
        if ((float)local_28 < (float)_DAT_008ec774 + local_30) {
          local_28 = (int)((float)_DAT_008ec774 + local_30);
        }
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec758,&local_30,local_58);
        if ((float)local_2c < (float)_DAT_008ec774 + local_30) {
          local_2c = (int)((float)_DAT_008ec774 + local_30);
        }
      }
      else {
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec78c,&local_18,local_50);
        if ((float)local_20 < (float)_DAT_008ec774 + local_18) {
          local_20 = (int)((float)_DAT_008ec774 + local_18);
        }
        FUN_00689ab0(DAT_0091552c,PTR_s_Player_008ec77c,&local_18,local_50);
        if ((float)local_24 < (float)_DAT_008ec774 + local_18) {
          local_24 = (int)((float)_DAT_008ec774 + local_18);
        }
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec724,&local_18,local_50);
        if ((float)local_28 < (float)_DAT_008ec774 + local_18) {
          local_28 = (int)((float)_DAT_008ec774 + local_18);
        }
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec758,&local_18,local_50);
        if ((float)local_2c < (float)_DAT_008ec774 + local_18) {
          local_2c = (int)((float)_DAT_008ec774 + local_18);
        }
        FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec750,&local_18,local_50);
        if ((float)local_38 < (float)_DAT_008ec774 + local_18) {
          local_38 = (int)((float)_DAT_008ec774 + local_18);
        }
      }
    }
    else {
      FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec78c,&local_14,local_4c);
      if ((float)local_20 < (float)_DAT_008ec774 + local_14) {
        local_20 = (int)((float)_DAT_008ec774 + local_14);
      }
      FUN_00689ab0(DAT_0091552c,PTR_s_Player_008ec77c,&local_14,local_4c);
      if ((float)local_24 < (float)_DAT_008ec774 + local_14) {
        local_24 = (int)((float)_DAT_008ec774 + local_14);
      }
      FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec724,&local_14,local_4c);
      if ((float)local_28 < (float)_DAT_008ec774 + local_14) {
        local_28 = (int)((float)_DAT_008ec774 + local_14);
      }
      FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec758,&local_14,local_4c);
      if ((float)local_2c < (float)_DAT_008ec774 + local_14) {
        local_2c = (int)((float)_DAT_008ec774 + local_14);
      }
      FUN_00689ab0(DAT_0091552c,PTR_DAT_008ec778,&local_14,local_4c);
      if ((float)local_38 < (float)_DAT_008ec774 + local_14) {
        local_38 = (int)((float)_DAT_008ec774 + local_14);
      }
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_70);
    local_3c = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_78);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      puVar2 = (undefined4 *)FUN_00421ec0();
      local_c = (short *)*puVar2;
      if (local_c != (short *)0x0) {
        if (DAT_0092017c < *(int *)(local_c + 0x22)) {
          DAT_0092017c = *(int *)(local_c + 0x22);
        }
        if (((DAT_00920178 == 0) && (uVar4 = size(), 1 < uVar4)) &&
           ((DAT_00920170 != 0 &&
            (iVar5 = FUN_005e0bc0(*(undefined4 *)(local_c + 2)), local_40 == iVar5)))) {
          _DAT_00920184 = 1;
        }
        local_44 = 0;
        local_54 = 0;
        local_5c = FUN_005771b0(*local_c);
        if ((local_5c != 0) && (*local_c != DAT_009180d4)) {
          uVar3 = FUN_00575f80(9999);
          local_44 = FUN_00627ee0(uVar3);
          local_54 = FUN_00575ff0();
          DAT_00920180 = 1;
        }
        if (local_40 == 0) {
          (&DAT_00920b88)[DAT_00920178] = DAT_00917588;
        }
        else {
          iVar5 = FUN_005e0bc0(*(undefined4 *)(local_c + 2));
          if (local_40 == iVar5) {
            (&DAT_00920b88)[DAT_00920178] = DAT_009175b0;
          }
          else {
            cVar1 = FUN_005e1310(*(undefined4 *)(local_c + 2));
            if (cVar1 == '\0') {
              (&DAT_00920b88)[DAT_00920178] = DAT_0091757c;
            }
            else {
              (&DAT_00920b88)[DAT_00920178] = DAT_00917578;
            }
          }
        }
        FUN_00689ab0(DAT_0091552c,&DAT_0088d764,&local_8,local_1c);
        _DAT_008ec774 = (int)(local_8 + 2.0);
        if (DAT_00920174 == 0) {
          if (DAT_00920170 == 0) {
            FUN_00689ab0(DAT_0091552c,local_c + 4,&local_8,local_1c);
            if ((float)local_20 < (float)_DAT_008ec774 + local_8) {
              local_20 = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 0x36,&local_8,local_1c);
            if ((float)local_24 < (float)_DAT_008ec774 + local_8) {
              local_24 = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 0x2c,&local_8,local_1c);
            if ((float)local_28 < (float)_DAT_008ec774 + local_8) {
              local_28 = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 9,&local_8,local_1c);
            if ((float)local_2c < (float)_DAT_008ec774 + local_8) {
              local_2c = (int)((float)_DAT_008ec774 + local_8);
            }
          }
          else {
            FUN_00689ab0(DAT_0091552c,local_c + 4,&local_8,local_1c);
            if ((float)local_20 < (float)_DAT_008ec774 + local_8) {
              local_20 = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 0x36,&local_8,local_1c);
            if ((float)local_24 < (float)_DAT_008ec774 + local_8) {
              local_24 = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 0x2c,&local_8,local_1c);
            if ((float)local_28 < (float)_DAT_008ec774 + local_8) {
              local_28 = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 9,&local_8,local_1c);
            if ((float)local_2c < (float)_DAT_008ec774 + local_8) {
              local_2c = (int)((float)_DAT_008ec774 + local_8);
            }
            FUN_00689ab0(DAT_0091552c,local_c + 0x1d,&local_8,local_1c);
            if ((float)local_38 < (float)_DAT_008ec774 + local_8) {
              local_38 = (int)((float)_DAT_008ec774 + local_8);
            }
          }
        }
        else {
          FUN_00689ab0(DAT_0091552c,local_c + 4,&local_8,local_1c);
          if ((float)local_20 < (float)_DAT_008ec774 + local_8) {
            local_20 = (int)((float)_DAT_008ec774 + local_8);
          }
          FUN_00689ab0(DAT_0091552c,local_c + 0x36,&local_8,local_1c);
          if ((float)local_24 < (float)_DAT_008ec774 + local_8) {
            local_24 = (int)((float)_DAT_008ec774 + local_8);
          }
          FUN_00689ab0(DAT_0091552c,local_c + 0x2c,&local_8,local_1c);
          if ((float)local_28 < (float)_DAT_008ec774 + local_8) {
            local_28 = (int)((float)_DAT_008ec774 + local_8);
          }
          FUN_00689ab0(DAT_0091552c,local_c + 9,&local_8,local_1c);
          if ((float)local_2c < (float)_DAT_008ec774 + local_8) {
            local_2c = (int)((float)_DAT_008ec774 + local_8);
          }
          FUN_00689ab0(DAT_0091552c,local_c + 0xe,&local_8,local_1c);
          if ((float)local_38 < (float)_DAT_008ec774 + local_8) {
            local_38 = (int)((float)_DAT_008ec774 + local_8);
          }
        }
      }
      FUN_0046b260(local_74,0);
    }
    if (DAT_00920174 == 0) {
      if (DAT_00920170 == 0) {
        local_34 = sprintf(&DAT_00920c08,"%s\t%s\t%s\t%s",PTR_DAT_008ec78c,PTR_s_Player_008ec77c,
                           PTR_DAT_008ec724,PTR_DAT_008ec758);
      }
      else {
        local_34 = sprintf(&DAT_00920c08,"%s\t%s\t%s\t%s\t%s",PTR_DAT_008ec78c,PTR_s_Player_008ec77c
                           ,PTR_DAT_008ec724,PTR_DAT_008ec758,PTR_DAT_008ec750);
      }
    }
    else {
      local_34 = sprintf(&DAT_00920c08,"%s\t%s\t%s\t%s\t%s",PTR_DAT_008ec78c,PTR_s_Player_008ec77c,
                         PTR_DAT_008ec724,PTR_DAT_008ec758,PTR_DAT_008ec778);
    }
    if (DAT_00920180 != 0) {
      sprintf(&DAT_00920c08 + local_34,"\t%s\t%s",PTR_DAT_008ec788,PTR_DAT_008ec74c);
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_7c);
    local_3c = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_84);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      puVar2 = (undefined4 *)FUN_00421ec0();
      local_10 = (short *)*puVar2;
      if (local_10 != (short *)0x0) {
        if (DAT_0092017c < *(int *)(local_10 + 0x22)) {
          DAT_0092017c = *(int *)(local_10 + 0x22);
        }
        if ((((DAT_00920178 == 0) && (uVar4 = size(), 1 < uVar4)) && (DAT_00920170 != 0)) &&
           (iVar5 = FUN_005e0bc0(*(undefined4 *)(local_10 + 2)), local_40 == iVar5)) {
          _DAT_00920184 = 1;
        }
        local_44 = 0;
        local_54 = 0;
        local_60 = FUN_005771b0(*local_10);
        if ((local_60 != 0) && (*local_10 != DAT_009180d4)) {
          uVar3 = FUN_00575f80(9999);
          local_44 = FUN_00627ee0(uVar3);
          local_54 = FUN_00575ff0();
          DAT_00920180 = 1;
        }
        if (local_40 == 0) {
          (&DAT_00920b88)[DAT_00920178] = DAT_00917588;
        }
        else {
          iVar5 = FUN_005e0bc0(*(undefined4 *)(local_10 + 2));
          if (local_40 == iVar5) {
            (&DAT_00920b88)[DAT_00920178] = DAT_009175b0;
          }
          else {
            cVar1 = FUN_005e1310(*(undefined4 *)(local_10 + 2));
            if (cVar1 == '\0') {
              (&DAT_00920b88)[DAT_00920178] = DAT_0091757c;
            }
            else {
              (&DAT_00920b88)[DAT_00920178] = DAT_00917578;
            }
          }
        }
        local_34 = 0;
        if (DAT_00920174 == 0) {
          if (DAT_00920170 == 0) {
            local_34 = sprintf(&DAT_00920188 + DAT_00920178 * 0x50,"%s\t%s\t%s\t%s",local_10 + 4,
                               local_10 + 0x36,local_10 + 0x2c,local_10 + 9);
          }
          else {
            local_34 = sprintf(&DAT_00920188 + DAT_00920178 * 0x50,"%s\t%s\t%s\t%s\t%s",local_10 + 4
                               ,local_10 + 0x36,local_10 + 0x2c,local_10 + 9,local_10 + 0x1d);
          }
        }
        else {
          local_34 = sprintf(&DAT_00920188 + DAT_00920178 * 0x50,"%s\t%s\t%s\t%s\t%s",local_10 + 4,
                             local_10 + 0x36,local_10 + 0x2c,local_10 + 9,local_10 + 0xe);
        }
        if (local_44 != 0) {
          sprintf(&DAT_00920188 + local_34 + DAT_00920178 * 0x50,"\t%lu\t%lu",local_44,local_54);
        }
        DAT_00920178 = DAT_00920178 + 1;
      }
      FUN_0046b260(local_80,0);
    }
    DAT_008ec75c = local_20;
    DAT_008ec760 = local_20 + local_24;
    DAT_008ec764 = DAT_008ec760 + local_28;
    DAT_008ec768 = DAT_008ec764 + local_2c;
    DAT_008ec76c = DAT_008ec768 + local_38;
    FUN_00626800();
    if (DAT_00917f4c != '\0') {
      DAT_0091815a = '\x01';
    }
  }
  return;
}

