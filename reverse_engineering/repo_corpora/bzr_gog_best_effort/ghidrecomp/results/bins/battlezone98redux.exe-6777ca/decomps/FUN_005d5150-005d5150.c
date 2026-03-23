
void FUN_005d5150(undefined4 param_1)

{
  char cVar1;
  undefined4 local_34;
  undefined4 local_30;
  int *local_28;
  int *local_24;
  undefined4 local_20;
  int *local_1c;
  void *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c9fc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  DAT_00918328 = param_1;
  local_20 = FUN_00435090(&local_34,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  DAT_0091832c = DAT_0091832c + 1;
  local_18 = operator_new(0x38);
  local_8 = 0;
  if (local_18 == (void *)0x0) {
    local_1c = (int *)0x0;
  }
  else {
    local_1c = (int *)FUN_007c6360(local_34,local_30,local_20);
  }
  local_24 = local_1c;
  local_8 = 0xffffffff;
  DAT_00918320 = local_1c;
  FUN_007c7930(DAT_00918328);
  cVar1 = FUN_007c7820();
  if (cVar1 != '\0') {
    local_28 = DAT_00918320;
    local_14 = DAT_00918320;
    if (DAT_00918320 != (int *)0x0) {
      (**(code **)(*DAT_00918320 + 0xc))(1);
    }
    DAT_00918320 = (int *)0x0;
  }
  DAT_0091832c = DAT_0091832c + -1;
  ExceptionList = local_10;
  return;
}

