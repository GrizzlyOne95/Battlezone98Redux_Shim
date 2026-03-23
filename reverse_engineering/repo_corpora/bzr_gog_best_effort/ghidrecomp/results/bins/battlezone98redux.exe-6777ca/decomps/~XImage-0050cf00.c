
/* Library Function - Single Match
    public: __thiscall CMFCRibbonInfo::XImage::~XImage(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall CMFCRibbonInfo::XImage::~XImage(XImage *this)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084ab73;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_004499a0(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = local_8 & 0xffffff00;
  FUN_004499a0();
  local_8 = 0xffffffff;
  FUN_004b6430();
  ExceptionList = local_10;
  return;
}

