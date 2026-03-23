
/* Library Function - Single Match
    public: virtual __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(void)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual Studio 2010 Debug */

void __thiscall CCachedDataPathProperty::~CCachedDataPathProperty(CCachedDataPathProperty *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008541d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  CDataPathProperty::~CDataPathProperty((CDataPathProperty *)(this + 0x40));
  local_8 = 0xffffffff;
  ATL::_ATL_BASE_MODULE70::~_ATL_BASE_MODULE70((_ATL_BASE_MODULE70 *)this);
  ExceptionList = local_10;
  return;
}

