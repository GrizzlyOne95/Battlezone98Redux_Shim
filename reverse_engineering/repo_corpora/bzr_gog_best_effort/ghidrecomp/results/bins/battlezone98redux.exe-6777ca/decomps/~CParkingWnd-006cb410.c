
/* Library Function - Single Match
    public: virtual __thiscall CParkingWnd::~CParkingWnd(void)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug */

void __thiscall CParkingWnd::~CParkingWnd(CParkingWnd *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008528b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00417c60(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = 0xffffffff;
  FUN_006cf8e0();
  ExceptionList = local_10;
  return;
}

