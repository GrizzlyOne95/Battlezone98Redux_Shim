/*
 * Entry: 0053696d
 * Name: PopperGunClass::PopperGunClass
 * Namespace: PopperGunClass
 * Signature: PopperGunClass * PopperGunClass(PopperGunClass * this, PopperGunClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PopperGunClass * __thiscall
PopperGunClass::PopperGunClass(PopperGunClass *this,PopperGunClass *param_1,long64 param_2)

{
  PopperGunClass *pPVar1;
  undefined4 unaff_EDI;
  
  pPVar1 = param_1;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xeaf36895,0xd9356908,&this->shotDelay,pPVar1->shotDelay)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xeaf36895,0x1af4cf34,&this->fireAngle,pPVar1->fireAngle)
  ;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
