
void FUN_005cc660(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = FUN_00462630(param_1);
  if ((local_c != 0) && (local_8 = FUN_004ff060(param_2), local_8 != 0)) {
    FUN_00477ce0();
    local_2c = param_3;
    local_28 = 0x15;
    local_24 = 0;
    local_20 = 0;
    local_10 = local_8 >> 0x1f;
    local_14 = local_8;
    FUN_004dbaf0(&local_2c);
  }
  return;
}

