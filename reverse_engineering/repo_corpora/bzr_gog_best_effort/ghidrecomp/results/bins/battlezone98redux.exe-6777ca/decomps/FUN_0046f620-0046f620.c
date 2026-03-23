
char FUN_0046f620(undefined4 param_1)

{
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  void *local_1c;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084641c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_11 = FUN_004ce1c0(param_1,"[AOIs]",DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (local_11 != '\0') {
    local_11 = FUN_004ce910(param_1,&local_28,4);
    if (local_11 != '\0') {
      for (local_18 = 0; (local_11 != '\0' && (local_18 < local_28)); local_18 = local_18 + 1) {
        local_1c = operator_new(0x18);
        local_8 = 0;
        if (local_1c == (void *)0x0) {
          local_20 = 0;
        }
        else {
          local_20 = FUN_0046f170();
        }
        local_8 = 0xffffffff;
        local_24 = local_20;
        local_11 = FUN_0046f840(param_1);
        FUN_00438be0(&local_24);
      }
    }
  }
  ExceptionList = local_10;
  return local_11;
}

