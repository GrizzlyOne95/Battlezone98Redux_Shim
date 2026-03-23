
void FUN_005cb790(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_c = FUN_00462630(param_1);
  if (local_c != 0) {
    FUN_00477ce0();
    local_2c = param_3;
    local_28 = param_2;
    local_24 = param_4;
    if (param_5 == 0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_00460fc0(param_5);
      local_8 = local_20;
      if (local_20 == 0) {
        return;
      }
    }
    local_1c = param_6;
    local_14 = param_7;
    local_10 = param_8;
    FUN_004dbaf0(&local_2c);
  }
  return;
}

