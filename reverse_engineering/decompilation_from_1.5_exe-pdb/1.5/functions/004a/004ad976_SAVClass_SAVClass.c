/*
 * Entry: 004ad976
 * Name: SAVClass::SAVClass
 * Namespace: SAVClass
 * Signature: SAVClass * SAVClass(SAVClass * this, SAVClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SAVClass * __thiscall SAVClass::SAVClass(SAVClass *this,SAVClass *param_1,long64 param_2)

{
  SAVClass *pSVar1;
  undefined4 unaff_EDI;
  
  pSVar1 = param_1;
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xdbba9577,0x2d6a7a45,(float *)(this + 1),
                   (float)pSVar1[1]._padding_);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
