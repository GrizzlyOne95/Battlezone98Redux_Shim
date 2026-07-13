
void __fastcall FUN_006b0950(int param_1)

{
  uint uVar1;
  undefined1 local_2c [8];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850490;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  FUN_006c8ce0(param_1 + 0x18);
  local_8 = 0;
  *(undefined1 *)(local_14 + 0xd8) = 1;
  *(undefined1 *)(local_14 + 0xd0) = 1;
  FUN_006c8de0(uVar1);
  if (*(int *)(local_14 + 0xd4) != 0) {
    FUN_006b0530();
    FUN_006ac600();
    local_20 = *(int *)(local_14 + 0xd4);
    local_1c = local_20;
    if (local_20 == 0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_006b0a90(1);
    }
    *(undefined4 *)(local_14 + 0xd4) = 0;
  }
  FUN_006c8f00();
  local_8._0_1_ = 1;
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    FUN_006c9330(local_2c);
  }
  FUN_006acc20(local_2c);
  FUN_006ad7d0(local_2c);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006c8f30();
  local_8 = 0xffffffff;
  FUN_006c8d50();
  ExceptionList = local_10;
  return;
}

