
/* WARNING: Removing unreachable block (ram,0x005c75ae) */

void FUN_005c7510(undefined4 param_1)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  int local_94;
  int local_90;
  uint local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  uint local_70;
  uint local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  uint local_5c;
  undefined4 local_58;
  uint local_54;
  int local_50;
  byte *local_4c;
  byte *local_48;
  byte *local_44;
  int local_40;
  byte *local_3c;
  byte *local_38;
  byte *local_34;
  byte *local_30;
  byte *local_2c;
  byte local_26;
  byte local_25;
  int local_24;
  byte local_1d;
  byte local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  char local_19;
  byte local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_02a13d64 = 0;
  DAT_02a13d88 = 0;
  DAT_02a13c7b = 0;
  for (local_40 = 0; local_40 < 0x10; local_40 = local_40 + 1) {
    *(undefined4 *)(&DAT_02a13d20 + local_40 * 4) = 0xffffffff;
  }
  FUN_00592490();
  DAT_02a13d84 = 0;
  if (DAT_009173b7 == '\0') {
    FUN_00438af0(param_1);
    local_74 = 0;
    local_18[0] = 0;
    local_19 = 1;
    if (DAT_00917b20 < 0x411) {
      cVar2 = FUN_004ce2f0(param_1,local_18,0xe);
      local_19 = cVar2 != '\0';
      local_54 = (uint)(byte)local_19;
      local_34 = &DAT_008767b4;
      local_2c = local_18;
      do {
        local_26 = *local_2c;
        bVar3 = local_26 < *local_34;
        if (local_26 != *local_34) {
LAB_005c7650:
          local_5c = -(uint)bVar3 | 1;
          goto LAB_005c7658;
        }
        if (local_26 == 0) break;
        local_1c = local_2c[1];
        bVar3 = local_1c < local_34[1];
        if (local_1c != local_34[1]) goto LAB_005c7650;
        local_2c = local_2c + 2;
        local_34 = local_34 + 2;
      } while (local_1c != 0);
      local_5c = 0;
LAB_005c7658:
      local_8c = local_5c;
      if (local_5c != 0) {
        local_48 = local_18;
        local_3c = (byte *)FUN_005ce740(0);
        do {
          bVar1 = *local_48;
          *local_3c = bVar1;
          local_48 = local_48 + 1;
          local_3c = local_3c + 1;
        } while (bVar1 != 0);
        DAT_02a13d84 = DAT_02a13d84 + 1;
        DAT_02a13d28 = 0;
        local_1a = 0;
      }
    }
    else {
      cVar2 = FUN_004ce910(param_1,&local_94,4);
      local_19 = cVar2 != '\0';
      local_70 = (uint)(byte)local_19;
      for (local_50 = 0; local_50 < local_94; local_50 = local_50 + 1) {
        if ((local_19 == '\0') || (cVar2 = FUN_004ce910(param_1,&local_90,4), cVar2 == '\0')) {
          local_64 = 0;
        }
        else {
          local_64 = 1;
        }
        local_19 = (char)local_64;
        if (((char)local_64 == '\0') || (cVar2 = FUN_004ce2f0(param_1,local_18,0xe), cVar2 == '\0'))
        {
          local_78 = 0;
        }
        else {
          local_78 = 1;
        }
        local_19 = (char)local_78;
        for (local_24 = 0; local_24 < DAT_02a13d84; local_24 = local_24 + 1) {
          local_38 = (byte *)FUN_005ce740(local_24);
          local_44 = local_18;
          do {
            local_25 = *local_44;
            bVar3 = local_25 < *local_38;
            if (local_25 != *local_38) {
LAB_005c7812:
              local_6c = -(uint)bVar3 | 1;
              goto LAB_005c781a;
            }
            if (local_25 == 0) break;
            local_1d = local_44[1];
            bVar3 = local_1d < local_38[1];
            if (local_1d != local_38[1]) goto LAB_005c7812;
            local_44 = local_44 + 2;
            local_38 = local_38 + 2;
          } while (local_1d != 0);
          local_6c = 0;
LAB_005c781a:
          if (local_6c == 0) break;
        }
        if (local_24 == DAT_02a13d84) {
          local_4c = local_18;
          local_30 = (byte *)FUN_005ce740(local_24);
          do {
            bVar1 = *local_4c;
            *local_30 = bVar1;
            local_4c = local_4c + 1;
            local_30 = local_30 + 1;
          } while (bVar1 != 0);
          DAT_02a13d84 = DAT_02a13d84 + 1;
          local_1b = 0;
        }
        *(int *)(&DAT_02a13d20 + local_90 * 4) = local_24;
      }
    }
    if ((local_19 == '\0') || (cVar2 = FUN_004ce910(param_1,&DAT_025cfa1c,4), cVar2 == '\0')) {
      local_80 = 0;
    }
    else {
      local_80 = 1;
    }
    local_19 = (char)local_80;
    if (((char)local_80 == '\0') || (cVar2 = FUN_004ce5e0(param_1,&DAT_02a13d64,1), cVar2 == '\0'))
    {
      local_88 = 0;
    }
    else {
      local_88 = 1;
    }
    local_19 = (char)local_88;
    if (((char)local_88 == '\0') || (cVar2 = FUN_004ce910(param_1,&DAT_009182a4,4), cVar2 == '\0'))
    {
      local_84 = 0;
    }
    else {
      local_84 = 1;
    }
    local_19 = (char)local_84;
    if (0x40c < DAT_00917b20) {
      if (((char)local_84 == '\0') || (cVar2 = FUN_004ceb10(param_1,&DAT_02a13d88,4), cVar2 == '\0')
         ) {
        local_7c = 0;
      }
      else {
        local_7c = 1;
      }
      local_19 = (char)local_7c;
    }
    if ((local_19 == '\0') || (cVar2 = FUN_0049ab50(param_1), cVar2 == '\0')) {
      local_58 = 0;
    }
    else {
      local_58 = 1;
    }
    local_19 = (char)local_58;
    if (((char)local_58 == '\0') || (cVar2 = FUN_004f4370(param_1), cVar2 == '\0')) {
      local_60 = 0;
    }
    else {
      local_60 = 1;
    }
    local_19 = (char)local_60;
    if (((char)local_60 == '\0') || (cVar2 = FUN_004a73a0(param_1), cVar2 == '\0')) {
      local_68 = 0;
    }
    else {
      local_68 = 1;
    }
    local_19 = (undefined1)local_68;
  }
  FUN_0083e885();
  return;
}

