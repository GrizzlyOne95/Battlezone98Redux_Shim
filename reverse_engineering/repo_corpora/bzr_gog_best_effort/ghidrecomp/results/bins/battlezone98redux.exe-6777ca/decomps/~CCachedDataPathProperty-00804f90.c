
/* Library Function - Single Match
    public: virtual __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(void)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug */

void __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(CCachedDataPathProperty *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008648b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00800170(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = 0xffffffff;
  FUN_00800170();
  ExceptionList = local_10;
  return;
}

