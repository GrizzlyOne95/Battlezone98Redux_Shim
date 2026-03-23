
/* Library Function - Single Match
    public: __thiscall CMFCRibbonInfo::XImage::~XImage(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall CMFCRibbonInfo::XImage::~XImage(XImage *this)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00858a93;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_0070ffe0(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = local_8 & 0xffffff00;
  FUN_006c9420();
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

