/*
 * Entry: 0052c6d0
 * Name: CannonClass::CannonClass
 * Namespace: CannonClass
 * Signature: CannonClass * CannonClass(CannonClass * this, CannonClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CannonClass * __thiscall
CannonClass::CannonClass(CannonClass *this,CannonClass *param_1,long64 param_2)

{
  CannonClass *pCVar1;
  undefined4 unaff_EDI;
  
  pCVar1 = param_1;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x6dbf0bc4,0xd9356908,&this->shotDelay,pCVar1->shotDelay)
  ;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
