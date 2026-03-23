
/* WARNING: Removing unreachable block (ram,0x00826280) */
/* WARNING: Removing unreachable block (ram,0x0082671c) */

void FUN_00826170(int *param_1,byte *param_2,uint param_3,byte *param_4,byte *param_5,int param_6,
                 undefined4 param_7)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  uint local_60;
  uint local_5c;
  uint local_4c;
  byte *local_40;
  byte *local_38;
  byte *local_34;
  byte *local_30;
  int local_2c;
  int local_28;
  byte local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  uint local_20;
  byte *local_1c;
  int local_18;
  byte *local_14;
  char local_10 [8];
  uint local_8;
  
  uVar5 = param_3;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  bVar4 = true;
  local_10[0] = '\0';
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_10[4] = 0;
  bVar1 = true;
  local_14 = param_2;
  bVar2 = false;
  bVar3 = false;
  local_18 = 0;
  local_2c = 0;
  local_28 = 0;
LAB_008261cf:
  if (bVar1) {
    bVar1 = false;
  }
  else {
    iVar6 = FUN_00826100(param_1,&param_1,param_7);
    if (iVar6 == 0) goto LAB_008266b5;
  }
  local_1c = (byte *)0x0;
  if (param_6 == 0) {
    local_20 = 0;
    for (local_14 = param_2; (local_20 < param_3 && (*param_1 != *(int *)local_14));
        local_14 = local_14 + 0x10) {
      local_20 = local_20 + 1;
    }
    if (local_20 == param_3) {
      strncpy(local_10,(char *)param_1,4);
      local_10[4] = 0;
      FUN_007d6830(s_Warning___unknown__s_chunk_found_008fe588,local_10);
    }
    iVar6 = FUN_008268c0(param_1,0,param_7);
    if (iVar6 != 0) goto LAB_008266b5;
  }
  else if (*param_1 == *(int *)local_14) {
    *(uint *)(local_14 + 0xc) = *(uint *)(local_14 + 0xc) | 0x80;
  }
  else {
    if ((local_18 != 0) || (!bVar2)) {
      iVar6 = FUN_00826140(&local_14,&param_3);
      if (iVar6 == 0) goto LAB_008266b5;
      local_18 = 0;
      local_2c = 0;
      iVar6 = FUN_008268c0(param_1,0,param_7);
      if (iVar6 == 0) {
        bVar1 = true;
      }
      goto LAB_008261cf;
    }
    if ((*(uint *)(local_14 + 0xc) & 4) == 0) {
      local_38 = &DAT_008a223c;
      local_40 = local_14;
      do {
        local_23 = *local_40;
        bVar7 = local_23 < *local_38;
        if (local_23 != *local_38) {
LAB_00826395:
          local_5c = -(uint)bVar7 | 1;
          goto LAB_0082639d;
        }
        if (local_23 == 0) break;
        local_21 = local_40[1];
        bVar7 = local_21 < local_38[1];
        if (local_21 != local_38[1]) goto LAB_00826395;
        local_40 = local_40 + 2;
        local_38 = local_38 + 2;
      } while (local_21 != 0);
      local_5c = 0;
LAB_0082639d:
      if (local_5c != 0) {
        if ((*(uint *)(local_14 + 0xc) & 8) != 0) {
          FUN_007d6830(s_Error___mandatory__s_chunk_not_f_008fe498,local_14);
        }
        if (((*(uint *)(local_14 + 0xc) & 0x10) != 0) || ((*(uint *)(local_14 + 0xc) & 0x20) != 0))
        goto LAB_0082676e;
        goto LAB_008266b5;
      }
    }
    else {
      FUN_007d65d0(s_Error___mandatory__s_chunk_not_f_008fe498,local_14);
    }
  }
  if ((*(uint *)(local_14 + 0xc) & 0x100) == 0) {
    if ((*(uint *)(local_14 + 0xc) & 0x200) == 0) {
      if (((local_18 == 0) || (local_2c == 0)) || ((*(uint *)(local_14 + 0xc) & 0x200) != 0)) {
        if ((*(uint *)(local_14 + 0xc) & 0x400) != 0) {
          local_18 = 1;
        }
      }
      else {
        FUN_007d6830(s_Warning___expected_count_chunk_008fe5ac);
      }
    }
    else {
      if (local_18 == 0) {
        local_18 = 1;
        bVar2 = true;
        if (bVar3) {
          bVar3 = false;
        }
        else {
          local_28 = 0;
          local_2c = 0;
        }
      }
      local_28 = local_28 + 1;
    }
  }
  else {
    if (local_18 != 0) {
      FUN_007d6830(s_Warning___too_many_count_chunks_f_008fe5cc);
    }
    local_1c = (byte *)&local_2c;
    local_28 = 0;
    bVar3 = true;
  }
  if ((*(uint *)(local_14 + 0xc) & 0x800) != 0) {
    if (local_1c != (byte *)0x0) {
      FUN_007d6830(s_Warning___attempt_made_to_pass_t_008fe504);
    }
    local_1c = param_4;
  }
  if ((*(uint *)(local_14 + 0xc) & 0x1000) != 0) {
    if (local_1c != (byte *)0x0) {
      FUN_007d6830(s_Warning___attempt_made_to_pass_t_008fe504);
    }
    local_1c = local_14;
  }
  if ((*(uint *)(local_14 + 0xc) & 0x2000) != 0) {
    if (local_1c != (byte *)0x0) {
      FUN_007d6830(s_Warning___attempt_made_to_pass_t_008fe504);
    }
    local_1c = param_5;
  }
  if (*(int *)(local_14 + 8) != 0) {
    local_4c = (uint)((*(uint *)(param_2 + 0xc) & 2) != 0);
    iVar6 = (**(code **)(local_14 + 8))(param_1 + local_4c * 2,local_1c,param_7);
    if (iVar6 == 0) {
      if ((param_6 == 0) || (iVar6 = FUN_008268c0(param_1,0,param_7), iVar6 == 0)) {
        if ((*(uint *)(local_14 + 0xc) & 4) == 0) {
          local_34 = &DAT_008a223c;
          local_30 = local_14;
          do {
            local_22 = *local_30;
            bVar7 = local_22 < *local_34;
            if (local_22 != *local_34) {
LAB_00826614:
              local_60 = -(uint)bVar7 | 1;
              goto LAB_0082661c;
            }
            if (local_22 == 0) break;
            local_24 = local_30[1];
            bVar7 = local_24 < local_34[1];
            if (local_24 != local_34[1]) goto LAB_00826614;
            local_30 = local_30 + 2;
            local_34 = local_34 + 2;
          } while (local_24 != 0);
          local_60 = 0;
LAB_0082661c:
          if (local_60 != 0) {
            if ((*(uint *)(local_14 + 0xc) & 8) != 0) {
              FUN_007d6830(s_Error___reading_of__s_chunk_fail_008fe4c0,local_14);
            }
            if (((*(uint *)(local_14 + 0xc) & 0x10) != 0) ||
               ((*(uint *)(local_14 + 0xc) & 0x20) != 0)) goto LAB_0082676e;
            if ((*(uint *)(local_14 + 0xc) & 0x200) == 0) goto LAB_008261cf;
          }
        }
        else {
          FUN_007d65d0(s_Error___reading_of__s_chunk_fail_008fe4c0,local_14);
        }
      }
      local_18 = 0;
      local_2c = 0;
    }
  }
  if (((local_18 != 0) || (param_6 == 0)) || (iVar6 = FUN_00826140(&local_14,&param_3), iVar6 != 0))
  goto LAB_008261cf;
LAB_008266b5:
  local_20 = 0;
  local_14 = param_2;
  do {
    if (uVar5 <= local_20) {
LAB_00826748:
      if (bVar4) {
        FUN_00826100(param_1,&param_1,param_7);
      }
      else {
        param_1 = (int *)0x0;
      }
LAB_0082676e:
      FUN_0083e885();
      return;
    }
    if (((*(uint *)(local_14 + 0xc) & 0x40) != 0) && ((*(uint *)(local_14 + 0xc) & 0x80) == 0)) {
      strncpy(local_10,(char *)local_14,4);
      local_10[4] = 0;
      FUN_007d65d0(s_Error___mandatory__s_chunk_not_f_008fe498,local_10);
      bVar4 = false;
      goto LAB_00826748;
    }
    local_20 = local_20 + 1;
    local_14 = local_14 + 0x10;
  } while( true );
}

