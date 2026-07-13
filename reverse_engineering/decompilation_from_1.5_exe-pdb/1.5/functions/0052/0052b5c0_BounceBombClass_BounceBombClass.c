/*
 * Entry: 0052b5c0
 * Name: BounceBombClass::BounceBombClass
 * Namespace: BounceBombClass
 * Signature: BounceBombClass * BounceBombClass(BounceBombClass * this, BounceBombClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BounceBombClass * __thiscall
BounceBombClass::BounceBombClass(BounceBombClass *this,BounceBombClass *param_1,long64 param_2)

{
  BounceBombClass *pBVar1;
  undefined4 unaff_EDI;
  
  pBVar1 = param_1;
  GrenadeClass::GrenadeClass
            ((GrenadeClass *)this,(GrenadeClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x5e574933,0xa7666fac,&this->bounceRatio,
                   pBVar1->bounceRatio);
  ParameterDB::Get((ParameterDB *)&param_1,0x5e574933,0x7e5a762c,this->soundBounce,0x10,
                   pBVar1->soundBounce);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
