/*
 * Entry: 004b3ac9
 * Name: TugClass::TugClass
 * Namespace: TugClass
 * Signature: TugClass * TugClass(TugClass * this, TugClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TugClass * __thiscall TugClass::TugClass(TugClass *this,TugClass *param_1,long64 param_2)

{
  int *piVar1;
  undefined4 unaff_EDI;
  
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_2,(char *)&this->_padding_);
  piVar1 = &this->_padding_;
  ParameterDB::Get((ParameterDB *)&param_2,0xdd64e901,0xb7295929,(char *)&this->_padding_,0x10,
                   (char *)piVar1);
  ParameterDB::Get((ParameterDB *)&param_2,0xdd64e901,0xe52080c2,(char *)&this->_padding_,0x10,
                   (char *)piVar1);
  ParameterDB::Get((ParameterDB *)&param_2,0xdd64e901,0x8019f006,(char *)&this->_padding_,0x10,
                   (char *)piVar1);
  ParameterDB::Get((ParameterDB *)&param_2,0xdd64e901,0x1292ac3d,(float *)(this + 1),
                   (float)param_1[1]._padding_);
  ParameterDB::~ParameterDB((ParameterDB *)&param_2);
  return this;
}
