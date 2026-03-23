
/* Library Function - Single Match
    public: __thiscall ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70(void)
   
   Library: Visual Studio 2005 Debug */

void __thiscall ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70(_ATL_WIN_MODULE70 *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085527b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  ~_String_val<>(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

