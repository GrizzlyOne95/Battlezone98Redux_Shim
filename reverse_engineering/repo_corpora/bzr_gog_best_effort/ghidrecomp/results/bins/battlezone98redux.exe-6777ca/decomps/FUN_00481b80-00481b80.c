
void FUN_00481b80(int *param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined1 local_50 [4];
  char *local_4c;
  char *local_48;
  uint local_44;
  uint local_40;
  int local_3c;
  uint local_38;
  char *local_34;
  char *local_30;
  char *local_2c;
  int local_28;
  char local_21;
  int local_20;
  char local_19;
  int *local_18;
  char *local_14;
  char local_10 [8];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_1 == (int *)0x0) {
    local_18 = &DAT_0091739c;
  }
  else {
    local_18 = param_1;
  }
  local_20 = FUN_004817a0(local_18,param_2);
  if (local_20 == 0) {
    if ((uint)local_18[2] <= (uint)local_18[1]) {
      if (local_18[3] == 0) {
        FUN_007d6830("BattleZone Memory running low (2)");
      }
      else {
        FUN_00481880(local_18,local_18[3]);
      }
    }
    local_28 = FUN_00829150(param_2);
    if (local_28 == 0) {
      FUN_007d6b70(&DAT_008767e0,&DAT_009467c0);
    }
    else {
      pcVar2 = strstr(param_2,".pak");
      if (pcVar2 != (char *)0x0) {
        local_14 = (char *)0x0;
      }
      while (local_14 = calloc(1,local_28 + 0x29), local_14 == (char *)0x0) {
        if (local_18[3] == 0) {
          FUN_007d6830("BattleZone Memory running low (1)");
          goto LAB_00481e87;
        }
        FUN_00481880(local_18,local_18[3]);
      }
      iVar1 = FUN_008290f0(param_2,local_50,local_14 + 0x28,local_28);
      if (iVar1 != 0) {
        local_3c = FUN_00481440(param_2);
        *(undefined4 *)(local_14 + 0x1c) = *(undefined4 *)(*local_18 + local_3c * 4);
        *(char **)(*local_18 + local_3c * 4) = local_14;
        local_14[0x14] = '\x01';
        local_14[0x15] = '\0';
        strncpy(local_14,param_2,0xf);
        *(int *)(local_14 + 0x10) = local_28;
        local_14[0x20] = '\0';
        local_14[0x21] = '\0';
        local_14[0x22] = '\0';
        local_14[0x23] = '\0';
        local_14[0x24] = '\0';
        local_14[0x25] = '\0';
        local_14[0x26] = '\0';
        local_14[0x27] = '\0';
        local_14[0x16] = '\0';
        local_2c = param_2;
        local_48 = param_2 + 1;
        do {
          local_21 = *local_2c;
          local_2c = local_2c + 1;
        } while (local_21 != '\0');
        local_44 = (int)local_2c - (int)local_48;
        local_40 = local_44;
        if (3 < local_44) {
          local_34 = param_2 + (local_44 - 4);
          pcVar2 = local_10;
          local_30 = pcVar2;
          do {
            local_19 = *local_34;
            *local_30 = local_19;
            local_34 = local_34 + 1;
            local_30 = local_30 + 1;
          } while (local_19 != '\0');
          _strlwr(local_10);
          local_4c = ".vdf.sdf.odf.stb.vxt.lgt.bzn.mat.hgt.hg2.trn";
          pcVar3 = strstr(".vdf.sdf.odf.stb.vxt.lgt.bzn.mat.hgt.hg2.trn",local_10);
          local_38 = (uint)(pcVar3 != (char *)0x0);
          local_14[0x16] = pcVar3 != (char *)0x0;
          if (local_14[0x16] != '\0') {
            uVar4 = FUN_004afe30(local_14 + 0x28,local_28,pcVar2);
            *(undefined4 *)(local_14 + 0x18) = uVar4;
          }
        }
        local_18[1] = local_18[1] + 1;
      }
    }
  }
  else {
    if (*(short *)(local_20 + 0x14) == 0) {
      FUN_00481550(local_18,local_20);
    }
    *(short *)(local_20 + 0x14) = *(short *)(local_20 + 0x14) + 1;
    if ((*(char *)(local_20 + 0x16) != '\0') &&
       (iVar1 = FUN_004afe30(local_20 + 0x28,*(undefined4 *)(local_20 + 0x10)),
       *(int *)(local_20 + 0x18) != iVar1)) {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
  }
LAB_00481e87:
  FUN_0083e885();
  return;
}

