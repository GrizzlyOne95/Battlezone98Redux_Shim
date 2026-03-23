
undefined4 * __fastcall FUN_0049a0f0(undefined4 *param_1)

{
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849448;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004b6260(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CockpitTimer::vftable;
  for (local_14 = 0; local_14 < 0xd; local_14 = local_14 + 1) {
    if (local_14 != 10) {
      FUN_004b6970(local_14,0);
    }
  }
  ExceptionList = local_10;
  return param_1;
}

