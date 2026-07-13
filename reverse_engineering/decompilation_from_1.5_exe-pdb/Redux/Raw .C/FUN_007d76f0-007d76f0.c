
void __fastcall FUN_007d76f0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00862e47;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 7;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x2f0));
  local_8._0_1_ = 6;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x2b0));
  local_8._0_1_ = 5;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x270));
  local_8._0_1_ = 4;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x230));
  local_8._0_1_ = 3;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x1f0));
  local_8._0_1_ = 2;
  FUN_007d7860();
  local_8._0_1_ = 1;
  FUN_007d7860();
  local_8 = (uint)local_8._1_3_ << 8;
  CBitmapButton::~CBitmapButton((CBitmapButton *)(param_1 + 0x20));
  local_8 = 0xffffffff;
  FUN_006e4470();
  ExceptionList = local_10;
  return;
}

