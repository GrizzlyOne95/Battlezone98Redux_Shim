
/* Library Function - Single Match
    public: __thiscall CPropertySheet::CPropertySheet(void)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual Studio 2010 Debug */

CPropertySheet * __thiscall CPropertySheet::CPropertySheet(CPropertySheet *this)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849d54;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004b6260();
  local_8 = 0;
  *(undefined ***)this = EditTerrain::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(this + 0xbc));
  local_8._0_1_ = 1;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(this + 0xc4));
  local_8 = CONCAT31(local_8._1_3_,2);
  CSliderCtrl::SetRange((CSliderCtrl *)this,10,0,uVar1);
  ExceptionList = local_10;
  return this;
}

