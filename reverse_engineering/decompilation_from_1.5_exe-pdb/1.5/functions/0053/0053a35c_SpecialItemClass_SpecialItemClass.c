/*
 * Entry: 0053a35c
 * Name: SpecialItemClass::SpecialItemClass
 * Namespace: SpecialItemClass
 * Signature: SpecialItemClass * SpecialItemClass(SpecialItemClass * this, SpecialItemClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpecialItemClass * __thiscall
SpecialItemClass::SpecialItemClass(SpecialItemClass *this,SpecialItemClass *param_1,long64 param_2)

{
  SpecialItemClass *pSVar1;
  undefined4 unaff_EDI;
  
  pSVar1 = param_1;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xef2ff121,0xd46356b6,this->activeSound,0x10,
                   pSVar1->activeSound);
  ParameterDB::Get((ParameterDB *)&param_1,0xef2ff121,0x6a2f4e9,this->expireSound,0x10,
                   pSVar1->expireSound);
  ParameterDB::Get((ParameterDB *)&param_1,0xef2ff121,0xe4af0ab6,&this->ammoCost,pSVar1->ammoCost);
  ParameterDB::Get((ParameterDB *)&param_1,0xef2ff121,0x682cd2b2,&this->triggerDelay,
                   pSVar1->triggerDelay);
  ParameterDB::Get((ParameterDB *)&param_1,0xef2ff121,0x2c5533ae,&this->reticleCount,
                   pSVar1->reticleCount);
  param_2._0_4_ = this->reticleCount + 1;
  this->triggerDelay = this->triggerDelay / (float)(int)param_2;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
