
void FUN_0058d090(float param_1,float param_2,float param_3,float param_4)

{
  int iVar1;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  param_1 = param_1 * DAT_02cc50e4;
  param_3 = param_3 * DAT_02cc50e4;
  param_4 = param_4 * DAT_02cc50e4;
  iVar1 = FUN_0058be00(param_2 * DAT_02cc50e4);
  local_8 = (int)((iVar1 - DAT_02cd9984) + (iVar1 - DAT_02cd9984 >> 0x1f & 0xfU)) >> 4;
  iVar1 = FUN_0058be30(param_4);
  iVar1 = (iVar1 - DAT_02cd9984) + 0xf;
  local_c = (int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4;
  iVar1 = FUN_0058be00(param_1);
  local_10 = (int)((iVar1 - DAT_02ce99c0) + (iVar1 - DAT_02ce99c0 >> 0x1f & 0xfU)) >> 4;
  iVar1 = FUN_0058be30(param_3);
  iVar1 = (iVar1 - DAT_02ce99c0) + 0xf;
  local_14 = (int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4;
  if ((((-1 < local_c) && (-1 < local_14)) && (local_8 < DAT_02a13c9c)) && (local_10 < DAT_02a13c70)
     ) {
    if (local_8 < 0) {
      local_8 = 0;
    }
    if (local_10 < 0) {
      local_10 = 0;
    }
    if (DAT_02a13c9c < local_c) {
      local_c = DAT_02a13c9c;
    }
    if (DAT_02a13c70 < local_14) {
      local_14 = DAT_02a13c70;
    }
    for (local_1c = local_8; local_1c < local_c; local_1c = local_1c + 1) {
      for (local_18 = local_10; local_18 < local_14; local_18 = local_18 + 1) {
        FUN_0058cf00(local_1c,local_18);
      }
    }
  }
  return;
}

