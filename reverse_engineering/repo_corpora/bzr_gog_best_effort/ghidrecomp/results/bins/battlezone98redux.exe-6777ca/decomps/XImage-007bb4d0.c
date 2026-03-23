
/* Library Function - Single Match
    public: __thiscall CMFCRibbonInfo::XImage::XImage(void)
   
   Library: Visual Studio 2010 Debug */

XImage * __thiscall CMFCRibbonInfo::XImage::XImage(XImage *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008617a3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00662ea0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_00662ea0();
  local_8 = CONCAT31(local_8._1_3_,1);
  basic_string<>();
  ExceptionList = local_10;
  return this;
}

