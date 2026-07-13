
/* Library Function - Single Match
    public: __thiscall AfxRibbonCollector::CMemoryDC::~CMemoryDC(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall AfxRibbonCollector::CMemoryDC::~CMemoryDC(CMemoryDC *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00858588;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0071b820(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = 0xffffffff;
  FUN_0071bb80();
  ExceptionList = local_10;
  return;
}

