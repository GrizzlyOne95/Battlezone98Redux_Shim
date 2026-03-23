
undefined4 * FUN_00461ba0(void)

{
  undefined4 *local_24;
  int local_20;
  int local_1c;
  void *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847404;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005d7300(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *local_14 = AiTask::vftable;
  if (DAT_0091737c == 0) {
    local_18 = operator_new(8);
    local_8._0_1_ = 1;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = vector<>();
    }
    local_20 = local_1c;
    local_8 = (uint)local_8._1_3_ << 8;
    DAT_0091737c = local_1c;
  }
  local_24 = local_14;
  FUN_00438be0(&local_24);
  ExceptionList = local_10;
  return local_14;
}

