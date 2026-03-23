
undefined4
FUN_007fd120(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined1 local_34 [16];
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22 [6];
  uint local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008645c0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_1c = 0;
  FUN_007fd2f0(local_34,param_2);
  local_8 = 0;
  FUN_007da4f0(&local_24,param_3);
  FUN_007da4f0(&local_23,param_4);
  FUN_007da4f0(local_22,param_5);
  local_8 = 1;
  uVar1 = FUN_00422f60(local_34);
  FUN_007fc6f0(uVar1);
  local_1c = local_1c | 1;
  local_8 = 0xffffffff;
  FUN_007fb7e0();
  ExceptionList = local_10;
  return param_1;
}

