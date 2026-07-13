
void __fastcall FUN_007fb250(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00864263;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_007d7920(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = local_8 & 0xffffff00;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x20));
  local_8 = 0xffffffff;
  FUN_006e4470();
  ExceptionList = local_10;
  return;
}

