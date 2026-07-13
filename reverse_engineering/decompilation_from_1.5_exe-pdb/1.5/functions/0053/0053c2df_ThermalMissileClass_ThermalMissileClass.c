/*
 * Entry: 0053c2df
 * Name: ThermalMissileClass::ThermalMissileClass
 * Namespace: ThermalMissileClass
 * Signature: ThermalMissileClass * ThermalMissileClass(ThermalMissileClass * this, ThermalMissileClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ThermalMissileClass * __thiscall
ThermalMissileClass::ThermalMissileClass
          (ThermalMissileClass *this,ThermalMissileClass *param_1,long64 param_2)

{
  ThermalMissileClass *pTVar1;
  undefined4 unaff_EDI;
  
  pTVar1 = param_1;
  MissileClass::MissileClass
            ((MissileClass *)this,(MissileClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x30403450,0xa3f03b49,&this->coneAngle,pTVar1->coneAngle)
  ;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
