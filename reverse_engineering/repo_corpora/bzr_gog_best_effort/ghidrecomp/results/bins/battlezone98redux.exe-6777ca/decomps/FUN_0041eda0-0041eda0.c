
undefined4 __thiscall
FUN_0041eda0(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  int local_30;
  int local_2c;
  int local_28;
  int local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00845152;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc2ccc & 1) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 1;
    local_8 = 0;
    basic_string<>("leftjoy");
    FUN_0083e979(FUN_008660b0);
  }
  if ((DAT_02cc2ccc & 2) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 2;
    local_8 = 1;
    basic_string<>("rightjoy");
    FUN_0083e979(FUN_008660a0);
  }
  if ((DAT_02cc2ccc & 4) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 4;
    local_8 = 2;
    basic_string<>("cmd_x");
    FUN_0083e979(FUN_00866090);
  }
  if ((DAT_02cc2ccc & 8) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 8;
    local_8 = 3;
    basic_string<>("cmd_y");
    FUN_0083e979(FUN_00866080);
  }
  if ((DAT_02cc2ccc & 0x10) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x10;
    local_8 = 4;
    basic_string<>("menu_pos");
    FUN_0083e979(FUN_00866070);
  }
  if ((DAT_02cc2ccc & 0x20) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x20;
    local_8 = 5;
    basic_string<>("menu_item");
    FUN_0083e979(FUN_00866060);
  }
  if ((DAT_02cc2ccc & 0x40) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x40;
    local_8 = 6;
    basic_string<>("menu_value");
    FUN_0083e979(FUN_00866050);
  }
  if ((DAT_02cc2ccc & 0x80) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x80;
    local_8 = 7;
    basic_string<>("strafe");
    FUN_0083e979(FUN_00866040);
  }
  if ((DAT_02cc2ccc & 0x100) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x100;
    local_8 = 8;
    basic_string<>("throttle_up");
    FUN_0083e979(FUN_00866030);
  }
  if ((DAT_02cc2ccc & 0x200) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x200;
    local_8 = 9;
    basic_string<>("throttle");
    FUN_0083e979(FUN_00866020);
  }
  if ((DAT_02cc2ccc & 0x400) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x400;
    local_8 = 10;
    basic_string<>("steer");
    FUN_0083e979(FUN_00866010);
  }
  if ((DAT_02cc2ccc & 0x800) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x800;
    local_8 = 0xb;
    basic_string<>("pitch");
    FUN_0083e979(FUN_00866000);
  }
  if ((DAT_02cc2ccc & 0x1000) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x1000;
    local_8 = 0xc;
    basic_string<>("track_pitch_delta");
    FUN_0083e979(FUN_00865ff0);
  }
  if ((DAT_02cc2ccc & 0x2000) == 0) {
    DAT_02cc2ccc = DAT_02cc2ccc | 0x2000;
    local_8 = 0xd;
    basic_string<>("track_yaw");
    FUN_0083e979(FUN_00865fe0);
  }
  local_8 = 0xffffffff;
  cVar1 = FUN_00427270(param_2,"default");
  if (cVar1 == '\0') {
    local_28 = param_2;
  }
  else {
    local_28 = param_1 + 0x44;
  }
  local_18 = FUN_0041d170(local_28,param_4);
  if ((local_18 == 0) || ((param_3 != 1 && ((*(uint *)(local_18 + 0x44) & 4) != 0)))) {
    local_18 = 0;
  }
  if (local_18 == 0) {
    if (param_3 == 0) {
      cVar2 = FUN_00427310(param_4,&DAT_02cc2d30);
      if (cVar2 == '\0') {
        cVar2 = FUN_00427310(param_4,&DAT_02cc2cb4);
        if (cVar2 != '\0') {
          if (cVar1 == '\0') {
            local_30 = param_2;
          }
          else {
            local_30 = param_1 + 0x44;
          }
          local_18 = FUN_0041d170(local_30,&DAT_02cc2d30);
        }
      }
      else {
        if (cVar1 == '\0') {
          local_2c = param_2;
        }
        else {
          local_2c = param_1 + 0x44;
        }
        local_18 = FUN_0041d170(local_2c,&DAT_02cc2cb4);
      }
    }
    if (((local_18 == 0) || (param_3 != 0)) || ((*(uint *)(local_18 + 0x44) & 4) == 0)) {
      local_18 = 0;
    }
  }
  if (local_18 != 0) {
    local_1c = 0;
    switch(param_5) {
    case 1:
      local_1c = local_18 + 0x48;
      if ((*(uint *)(local_18 + 0x60) & 1) != 0) {
        param_5 = 1;
      }
      break;
    case 2:
      local_1c = local_18 + 0x48;
      if ((*(uint *)(local_18 + 0x60) & 1) != 0) {
        param_5 = 2;
      }
      break;
    case 3:
      local_1c = local_18 + 0x2c;
      if ((*(uint *)(local_18 + 0x44) & 1) != 0) {
        param_5 = 4;
      }
      break;
    case 4:
      local_1c = local_18 + 0x2c;
      if ((*(uint *)(local_18 + 0x44) & 1) != 0) {
        param_5 = 3;
      }
    }
    switch(param_5) {
    case 0:
      if (((*(uint *)(local_18 + 0x44) & 2) == 0) && ((*(uint *)(local_18 + 0x60) & 2) == 0)) {
        ExceptionList = local_10;
        return 0;
      }
      uVar3 = FUN_0081cb40("input_config",&DAT_00871468);
      ExceptionList = local_10;
      return uVar3;
    case 1:
    case 3:
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2d00);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","forward");
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2d60);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","forward");
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2dc4);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","turn_left");
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2ce8);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","strafe_right");
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2ddc);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","pitch_up");
        ExceptionList = local_10;
        return uVar3;
      }
    case 2:
    case 4:
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2d60);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config",&DAT_008714b0);
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2dc4);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","turn_right");
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2ce8);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","strafe_left");
        ExceptionList = local_10;
        return uVar3;
      }
      cVar1 = FUN_00427310(local_1c,&DAT_02cc2ddc);
      if (cVar1 != '\0') {
        uVar3 = FUN_0081cb40("input_config","pitch_down");
        ExceptionList = local_10;
        return uVar3;
      }
    }
  }
  ExceptionList = local_10;
  return 0;
}

