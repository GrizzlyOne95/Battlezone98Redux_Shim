
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0069d630(code *param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_28 = param_3 / 0x18;
  local_24 = param_4 / 0x18;
  local_30 = (param_5 + 0x17) / 0x18;
  local_2c = (param_6 + 0x17) / 0x18;
  local_14 = (int)((local_24 - _DAT_00931000) + (local_24 - _DAT_00931000 >> 0x1f & 0xfU)) >> 4;
  local_1c = (int)((local_28 - _DAT_0093100c) + (local_28 - _DAT_0093100c >> 0x1f & 0xfU)) >> 4;
  local_18 = (int)(local_2c + 0xf + (local_2c + 0xf >> 0x1f & 0xfU)) >> 4;
  local_20 = (int)(local_30 + 0xf + (local_30 + 0xf >> 0x1f & 0xfU)) >> 4;
  if (local_14 < 0) {
    local_14 = 0;
  }
  if (DAT_00931010 < local_18) {
    local_18 = DAT_00931010;
  }
  if (local_1c < 0) {
    local_1c = 0;
  }
  if (DAT_00931004 < local_20) {
    local_20 = DAT_00931004;
  }
  for (local_10 = local_14; local_10 < local_18; local_10 = local_10 + 1) {
    for (local_c = local_1c; local_c < local_20; local_c = local_c + 1) {
      iVar1 = *(int *)(*(int *)(DAT_00931008 + local_10 * 4) + 0x100 + local_c * 0x10c);
      while (local_8 = iVar1, local_8 != 0) {
        iVar1 = *(int *)(local_8 + 0x10);
        FUN_006a5f20(*(undefined4 *)(local_8 + 0x18),&local_34,&local_38,&local_3c,&local_40);
        if ((((local_34 < param_5) && (local_38 < param_6)) && (param_3 < local_3c)) &&
           (param_4 < local_40)) {
          (*param_1)(local_8,param_2);
        }
      }
    }
  }
  return;
}

