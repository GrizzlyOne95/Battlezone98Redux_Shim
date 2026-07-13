/*
 * Entry: 0049fc4d
 * Name: MinelayerClass::MinelayerClass
 * Namespace: MinelayerClass
 * Signature: MinelayerClass * MinelayerClass(MinelayerClass * this, MinelayerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MinelayerClass * __thiscall
MinelayerClass::MinelayerClass(MinelayerClass *this,MinelayerClass *param_1,long64 param_2)

{
  MinelayerClass *pMVar1;
  undefined4 unaff_EDI;
  
  pMVar1 = param_1;
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x21433f4d,0x5cb1a709,&this->mineDist,pMVar1->mineDist);
  ParameterDB::Get((ParameterDB *)&param_1,0x21433f4d,0x341e56e4,(float *)&this->field_0x3c4,
                   *(float *)&pMVar1->field_0x3c4);
  ParameterDB::Get((ParameterDB *)&param_1,0x21433f4d,0xfea35bca,(float *)(this + 1),
                   (float)pMVar1[1]._padding_);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
