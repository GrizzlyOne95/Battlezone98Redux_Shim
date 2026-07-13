
void __fastcall FUN_0080b1d0(undefined4 *param_1)

{
  char cVar1;
  shared_ptr<class___ExceptionPtr> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>(local_14);
  local_8 = 0;
  cVar1 = FUN_00808e30(*param_1,param_1[1],param_1[2],param_1[3],local_2c);
  if (cVar1 == '\0') {
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
              (local_2c,(__ExceptionPtr *)param_1[4]);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

