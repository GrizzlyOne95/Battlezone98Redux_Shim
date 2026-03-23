
undefined4
FUN_00784620(double param_1,double param_2,double param_3,float param_4,float param_5,float param_6,
            float *param_7,undefined4 param_8)

{
  int iVar1;
  int local_44;
  int local_40;
  float local_3c;
  float local_38;
  uint local_34;
  int local_30;
  int local_2c;
  uint local_28;
  uint local_24;
  float local_20;
  float local_1c;
  float local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  param_1 = (double)DAT_02cc50e4 * param_1;
  param_2 = (double)DAT_02cc50e4 * param_2;
  param_3 = (double)DAT_02cc50e4 * param_3;
  param_4 = param_4 * DAT_02cc50e4;
  param_5 = param_5 * DAT_02cc50e4;
  param_6 = param_6 * DAT_02cc50e4;
  local_8 = FUN_0046eaf0(param_1);
  local_10 = FUN_0046eaf0((double)(*param_7 * param_4) + param_1);
  local_c = FUN_0046eaf0(param_3);
  local_14 = FUN_0046eaf0((double)(*param_7 * param_6) + param_3);
  local_3c = (float)((param_1 - 0.5) - (double)local_8);
  local_40 = 1;
  local_38 = (float)((param_3 - 0.5) - (double)local_c);
  local_44 = 1;
  local_28 = FUN_00784000(local_8,local_c);
  local_34 = FUN_00784000(local_10,local_14);
  while (local_28 != 0 || local_34 != 0) {
    if ((local_28 & local_34) != 0) {
      return 0;
    }
    local_24 = local_28;
    if (local_28 == 0) {
      local_24 = local_34;
    }
    if ((local_24 & 8) == 0) {
      if ((local_24 & 4) == 0) {
        if ((local_24 & 2) == 0) {
          local_2c = FUN_00783ff0(local_10 - local_8,DAT_02ce99c4 - local_c);
          local_2c = local_2c + local_8;
          local_30 = DAT_02ce99c4;
        }
        else {
          local_2c = FUN_00783ff0(local_10 - local_8,DAT_02cd9984 - local_c);
          local_2c = local_2c + local_8;
          local_30 = DAT_02cd9984;
        }
      }
      else {
        local_30 = FUN_00783ff0(local_14 - local_c,DAT_02ce99a0 - local_8);
        local_30 = local_30 + local_c;
        local_2c = DAT_02ce99a0;
      }
    }
    else {
      local_30 = FUN_00783ff0(local_14 - local_c,DAT_02ce99c0 - local_8);
      local_30 = local_30 + local_c;
      local_2c = DAT_02ce99c0;
    }
    if (local_24 == local_28) {
      local_8 = local_2c;
      local_c = local_30;
      local_28 = FUN_00784000();
    }
    else {
      local_10 = local_2c;
      local_14 = local_30;
      local_34 = FUN_00784000();
    }
  }
  local_10 = local_10 - local_8;
  local_14 = local_14 - local_c;
  local_20 = param_4;
  if (param_4 < 0.0) {
    local_3c = -local_3c;
    local_10 = -local_10;
    local_40 = -1;
    local_20 = -param_4;
  }
  local_1c = param_6;
  if (param_6 < 0.0) {
    local_38 = -local_38;
    local_14 = -local_14;
    local_44 = -1;
    local_1c = -param_6;
  }
  if (local_20 <= local_1c) {
    local_18 = (0.5 - local_38) * local_20 - (0.5 - local_3c) * local_1c;
    while (-1 < local_14) {
      iVar1 = FUN_00784180(local_8,local_c,param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                           param_8);
      if (iVar1 != 0) {
        return 1;
      }
      if (0.0 < local_18) {
        local_8 = local_8 + local_40;
        local_18 = local_18 - local_1c;
        iVar1 = FUN_00784180(local_8,local_c,param_1,param_2,param_3,param_4,param_5,param_6,param_7
                             ,param_8);
        if (iVar1 != 0) {
          return 1;
        }
      }
      local_c = local_c + local_44;
      local_18 = local_18 + local_20;
      local_14 = local_14 + -1;
    }
  }
  else {
    local_18 = (0.5 - local_3c) * local_1c - (0.5 - local_38) * local_20;
    while (-1 < local_10) {
      iVar1 = FUN_00784180(local_8,local_c,param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                           param_8);
      if (iVar1 != 0) {
        return 1;
      }
      if (0.0 < local_18) {
        local_c = local_c + local_44;
        local_18 = local_18 - local_20;
        iVar1 = FUN_00784180(local_8,local_c,param_1,param_2,param_3,param_4,param_5,param_6,param_7
                             ,param_8);
        if (iVar1 != 0) {
          return 1;
        }
      }
      local_8 = local_8 + local_40;
      local_18 = local_18 + local_1c;
      local_10 = local_10 + -1;
    }
  }
  return 0;
}

