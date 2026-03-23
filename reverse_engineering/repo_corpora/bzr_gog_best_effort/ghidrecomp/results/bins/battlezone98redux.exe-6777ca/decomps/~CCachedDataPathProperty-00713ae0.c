
/* Library Function - Single Match
    public: virtual __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(CCachedDataPathProperty *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00857c48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006e0630(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

