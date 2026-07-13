
undefined1 FUN_0080ca60(void)

{
  char cVar1;
  shared_ptr<class___ExceptionPtr> local_28 [16];
  undefined4 *local_18;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864b18;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006cc0e0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  cVar1 = FUN_007fd3e0(*local_18,local_18[1],local_18[2],local_18[3],local_28);
  if (cVar1 == '\0') {
    local_12 = 0;
    local_8 = 0xffffffff;
    FUN_006c3d30();
    local_11 = local_12;
  }
  else {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
              (local_28,(__ExceptionPtr *)local_18[4]);
    local_11 = 1;
    local_8 = 0xffffffff;
    FUN_006c3d30();
  }
  ExceptionList = local_10;
  return local_11;
}

