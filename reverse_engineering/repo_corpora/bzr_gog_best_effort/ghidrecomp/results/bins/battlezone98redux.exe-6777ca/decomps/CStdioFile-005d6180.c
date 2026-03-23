
/* Library Function - Single Match
    public: __thiscall CStdioFile::CStdioFile(void)
   
   Library: Visual Studio 2010 Debug */

CStdioFile * __thiscall CStdioFile::CStdioFile(CStdioFile *this)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008493d8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004b6260();
  local_8 = 0;
  *(undefined ***)this = SniperInterface::vftable;
  CSliderCtrl::SetRange((CSliderCtrl *)this,0,-1,uVar1);
  ExceptionList = local_10;
  return this;
}

