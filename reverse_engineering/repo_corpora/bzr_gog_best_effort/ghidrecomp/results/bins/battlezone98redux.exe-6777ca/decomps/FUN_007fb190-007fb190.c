
void __fastcall FUN_007fb190(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0086422b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 5;
  ~<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x1b0));
  local_8._0_1_ = 4;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x170));
  local_8._0_1_ = 3;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x130));
  local_8._0_1_ = 2;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0xf0));
  local_8._0_1_ = 1;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0xb0));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007fb250();
  local_8 = 0xffffffff;
  FUN_006e4470();
  ExceptionList = local_10;
  return;
}

