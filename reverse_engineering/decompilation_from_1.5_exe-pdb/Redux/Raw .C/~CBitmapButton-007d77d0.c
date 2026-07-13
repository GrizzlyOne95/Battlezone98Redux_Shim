
/* Library Function - Single Match
    public: virtual __thiscall CBitmapButton::~CBitmapButton(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall CBitmapButton::~CBitmapButton(CBitmapButton *this)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00862e9c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 3;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(this + 0xd0));
  local_8._0_1_ = 2;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(this + 0x90));
  local_8._0_1_ = 1;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(this + 0x50));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d7920(uVar1);
  local_8 = 0xffffffff;
  FUN_006e4470();
  ExceptionList = local_10;
  return;
}

