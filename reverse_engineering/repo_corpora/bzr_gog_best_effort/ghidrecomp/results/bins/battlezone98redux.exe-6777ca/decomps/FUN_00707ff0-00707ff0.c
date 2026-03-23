
void __fastcall FUN_00707ff0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085730c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 3;
  if (*(int *)(param_1 + 200) != 0) {
    FUN_006affd0(*(undefined4 *)(param_1 + 200),DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  local_8._0_1_ = 2;
  ATL::_ATL_BASE_MODULE70::~_ATL_BASE_MODULE70((_ATL_BASE_MODULE70 *)(param_1 + 0x80));
  local_8._0_1_ = 1;
  FUN_006d1230();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006c9420();
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

