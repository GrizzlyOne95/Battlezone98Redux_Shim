
undefined4 * __fastcall FUN_004b6260(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  void *local_2c;
  undefined4 local_28;
  void *local_24;
  undefined4 local_20;
  void *local_1c;
  undefined4 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849a24;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = DisplayInterface::vftable;
  param_1[1] = 0;
  local_18 = param_1;
  if (DAT_02cc2b98 == 0) {
    local_1c = operator_new(8);
    local_8 = 0;
    if (local_1c == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = vector<>();
    }
    local_34 = local_20;
    DAT_0260d760 = local_20;
    for (local_14 = 0; local_8 = 0xffffffff, local_14 < 0xd; local_14 = local_14 + 1) {
      local_24 = operator_new(8);
      local_8 = 1;
      if (local_24 == (void *)0x0) {
        local_28 = 0;
      }
      else {
        local_28 = vector<>(uVar1);
      }
      local_38 = local_28;
      local_8 = 0xffffffff;
      *(undefined4 *)(&DAT_0260d764 + local_14 * 4) = local_28;
      local_2c = operator_new(8);
      local_8 = 2;
      if (local_2c == (void *)0x0) {
        local_30 = 0;
      }
      else {
        local_30 = vector<>();
      }
      local_3c = local_30;
      *(undefined4 *)(&DAT_0260d79c + local_14 * 4) = local_30;
    }
    DAT_02cc2b98 = 1;
  }
  local_8 = 0xffffffff;
  local_40 = local_18;
  FUN_00438be0(&local_40);
  ExceptionList = local_10;
  return local_18;
}

