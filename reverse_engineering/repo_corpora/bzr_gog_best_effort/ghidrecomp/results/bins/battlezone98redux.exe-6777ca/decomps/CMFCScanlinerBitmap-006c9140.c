
/* Library Function - Single Match
    public: __thiscall CMFCScanlinerBitmap::CMFCScanlinerBitmap(void)
   
   Library: Visual Studio 2010 Debug */

CMFCScanlinerBitmap * __thiscall CMFCScanlinerBitmap::CMFCScanlinerBitmap(CMFCScanlinerBitmap *this)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>((allocator<char> *)this);
  local_8 = 0;
  FUN_006cd940(uVar1);
  ExceptionList = local_10;
  return this;
}

