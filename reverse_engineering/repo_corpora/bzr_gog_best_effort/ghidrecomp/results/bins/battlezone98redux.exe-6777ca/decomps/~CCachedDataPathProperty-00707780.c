
/* Library Function - Single Match
    public: virtual __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(void)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual Studio 2010 Debug */

void __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(CCachedDataPathProperty *this)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856c68;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  CDataPathProperty::~CDataPathProperty((CDataPathProperty *)(this + 0x28));
  local_8 = 0xffffffff;
  FUN_004bb3d0(uVar1);
  ExceptionList = local_10;
  return;
}

