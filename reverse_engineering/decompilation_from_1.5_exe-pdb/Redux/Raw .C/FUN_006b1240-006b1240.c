
void FUN_006b1240(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_28 [8];
  undefined4 local_20;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850548;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_11 = '\0';
  FUN_006c8f00(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    cVar1 = FUN_006c92a0(param_1,local_28,param_2);
    if ((cVar1 == '\0') && (local_11 == '\0')) {
      local_20 = 0;
    }
    else {
      local_20 = 1;
    }
    local_11 = (char)local_20;
  }
  FUN_006ad700(local_28);
  if (local_11 != '\0') {
    FUN_006b0530();
  }
  local_8 = 0xffffffff;
  FUN_006c8f30();
  ExceptionList = local_10;
  return;
}

