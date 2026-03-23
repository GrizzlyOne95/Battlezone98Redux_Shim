
int FUN_00692030(undefined4 *param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                int *param_6,int *param_7)

{
  int iVar1;
  int iVar2;
  int local_2c;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_1c = 0;
  local_18 = 0;
  do {
    iVar1 = FUN_00690c40(param_2,local_18,&local_8,&local_c);
    if (iVar1 != 0) {
      local_10 = param_4 - local_8;
      if (local_10 < 0) {
        local_10 = -local_10;
      }
      local_14 = param_5 - local_c;
      if (local_14 < 0) {
        local_14 = -local_14;
      }
      if (local_14 < local_10) {
        local_20 = local_10;
      }
      else {
        local_20 = local_14;
      }
      if ((local_1c == 0) || (local_20 < local_2c)) {
        local_8 = local_8 - ((*(uint *)(param_3 + 0x24) >> 0x12 & 0xf) >> 1);
        local_c = local_c - ((*(uint *)(param_3 + 0x24) >> 0x16 & 0xf) >> 1);
        iVar2 = FUN_00691dd0(*param_1,param_3,local_8,local_c,&local_8,&local_c);
        if (iVar2 != 0) {
          local_2c = local_20;
          local_1c = 1;
          *param_6 = local_8;
          *param_7 = local_c;
        }
      }
    }
    local_18 = local_18 + 1;
  } while (iVar1 != 0);
  return local_1c;
}

