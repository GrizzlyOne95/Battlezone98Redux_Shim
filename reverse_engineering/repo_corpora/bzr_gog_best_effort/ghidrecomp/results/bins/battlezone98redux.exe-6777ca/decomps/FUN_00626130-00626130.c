
/* WARNING: Removing unreachable block (ram,0x006261d9) */
/* WARNING: Removing unreachable block (ram,0x0062627a) */

void FUN_00626130(int param_1,int param_2,char param_3,int param_4)

{
  char *pcVar1;
  undefined4 uVar2;
  size_t sVar3;
  undefined1 *local_74;
  undefined1 *local_6c;
  undefined1 *local_68;
  undefined1 *local_60;
  undefined1 *local_58;
  undefined1 *local_54;
  char local_50 [36];
  char local_2c [36];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (0 < param_1) {
    local_2c[0] = '\0';
    local_2c[1] = '\0';
    local_2c[2] = '\0';
    local_2c[3] = '\0';
    local_2c[4] = '\0';
    local_2c[5] = '\0';
    local_2c[6] = '\0';
    local_2c[7] = '\0';
    local_2c[8] = '\0';
    local_2c[9] = '\0';
    local_2c[10] = '\0';
    local_2c[0xb] = '\0';
    local_2c[0xc] = '\0';
    local_2c[0xd] = '\0';
    local_2c[0xe] = '\0';
    local_2c[0xf] = '\0';
    local_2c[0x10] = '\0';
    local_2c[0x11] = '\0';
    local_2c[0x12] = '\0';
    local_2c[0x13] = '\0';
    local_2c[0x14] = '\0';
    local_2c[0x15] = '\0';
    local_2c[0x16] = '\0';
    local_2c[0x17] = '\0';
    local_2c[0x18] = '\0';
    local_2c[0x19] = '\0';
    local_2c[0x1a] = '\0';
    local_2c[0x1b] = '\0';
    local_2c[0x1c] = '\0';
    local_2c[0x1d] = '\0';
    local_2c[0x1e] = '\0';
    local_2c[0x1f] = '\0';
    local_2c[0x20] = '\0';
    if (*(int *)(&DAT_009180e8 + param_1 * 4) == 0) {
      uVar2 = FUN_0081cb40("multi_three",&DAT_008757b0,param_1);
      sprintf(local_2c,"%s %d",uVar2);
    }
    else {
      sVar3 = 0x20;
      pcVar1 = (char *)FUN_0041f870();
      strncpy(local_2c,pcVar1,sVar3);
    }
                    /* WARNING: Ignoring partial resolution of indirect */
    local_2c[0x20] = 0;
    local_50[0] = '\0';
    local_50[1] = '\0';
    local_50[2] = '\0';
    local_50[3] = '\0';
    local_50[4] = '\0';
    local_50[5] = '\0';
    local_50[6] = '\0';
    local_50[7] = '\0';
    local_50[8] = '\0';
    local_50[9] = '\0';
    local_50[10] = '\0';
    local_50[0xb] = '\0';
    local_50[0xc] = '\0';
    local_50[0xd] = '\0';
    local_50[0xe] = '\0';
    local_50[0xf] = '\0';
    local_50[0x10] = '\0';
    local_50[0x11] = '\0';
    local_50[0x12] = '\0';
    local_50[0x13] = '\0';
    local_50[0x14] = '\0';
    local_50[0x15] = '\0';
    local_50[0x16] = '\0';
    local_50[0x17] = '\0';
    local_50[0x18] = '\0';
    local_50[0x19] = '\0';
    local_50[0x1a] = '\0';
    local_50[0x1b] = '\0';
    local_50[0x1c] = '\0';
    local_50[0x1d] = '\0';
    local_50[0x1e] = '\0';
    local_50[0x1f] = '\0';
    local_50[0x20] = '\0';
    if (0 < param_2) {
      if (*(int *)(&DAT_009180e8 + param_2 * 4) == 0) {
        uVar2 = FUN_0081cb40("multi_three",&DAT_008757b0,param_2);
        sprintf(local_50,"%s %d",uVar2);
      }
      else {
        sVar3 = 0x20;
        pcVar1 = (char *)FUN_0041f870();
        strncpy(local_50,pcVar1,sVar3);
      }
    }
                    /* WARNING: Ignoring partial resolution of indirect */
    local_50[0x20] = 0;
    if (param_3 == 'P') {
      if (param_2 < 1) {
        if (param_4 == 0) {
          local_54 = PTR_s__s_pilot_008ec754;
        }
        else {
          local_54 = &DAT_008a1ad8;
        }
        FUN_0056fcb0("%s%s %s",local_2c,local_54,PTR_s_killed_008ec734);
      }
      else {
        if (param_4 == 0) {
          local_6c = PTR_s__s_pilot_008ec754;
        }
        else {
          local_6c = &DAT_008a1ad8;
        }
        FUN_0056fcb0("%s%s %s %s",local_2c,local_6c,PTR_s_killed_by_008ec790,local_50);
      }
    }
    else if (param_3 == 'B') {
      if (param_2 < 1) {
        if (param_4 == 0) {
          local_58 = PTR_s__s_building_destroyed_008ec72c;
        }
        else {
          local_58 = &DAT_008a1ad8;
        }
        FUN_0056fcb0(&DAT_0088d944,local_2c,local_58);
      }
      else {
        if (param_4 == 0) {
          local_74 = PTR_s__s_building_destroyed_by_008ec780;
        }
        else {
          local_74 = &DAT_008a1ad8;
        }
        FUN_0056fcb0("%s%s %s",local_2c,local_74,local_50);
      }
    }
    else if (param_3 == 'S') {
      if (param_2 < 1) {
        if (param_4 == 0) {
          local_68 = PTR_s__s_pilot_008ec754;
        }
        else {
          local_68 = &DAT_008a1ad8;
        }
        FUN_0056fcb0("%s%s %s",local_2c,local_68,PTR_s_sniped_008ec770);
      }
      else {
        if (param_4 == 0) {
          local_60 = PTR_s__s_pilot_008ec754;
        }
        else {
          local_60 = &DAT_008a1ad8;
        }
        FUN_0056fcb0("%s%s %s %s",local_2c,local_60,PTR_s_sniped_by_008ec728,local_50);
      }
    }
    else if (param_3 == 'E') {
      FUN_0056fcb0("%s %s",local_2c,PTR_s_ejected_008ec730);
    }
    else if (param_2 < 1) {
      FUN_0056fcb0(&DAT_0088d944,local_2c,PTR_s__s_ship_destroyed_008ec738);
    }
    else {
      FUN_0056fcb0("%s%s %s",local_2c,PTR_s__s_ship_destroyed_by_008ec73c,local_50);
    }
  }
  FUN_0083e885();
  return;
}

