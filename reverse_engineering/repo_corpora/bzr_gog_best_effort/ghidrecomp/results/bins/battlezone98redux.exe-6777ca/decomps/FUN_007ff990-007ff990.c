
void FUN_007ff990(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uStack_50;
  undefined4 local_20 [2];
  char local_16;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864720;
  local_10 = ExceptionList;
  uStack_50 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_50;
  ExceptionList = &local_10;
  allocator<>(param_1);
  local_8 = 0;
  local_20[0] = *param_1;
  local_16 = FUN_007ff0b0(local_20,param_2,param_3,param_4);
  if (local_16 != '\0') {
    *param_1 = local_20[0];
  }
  local_15 = local_16;
  FUN_007ffacf();
  return;
}

