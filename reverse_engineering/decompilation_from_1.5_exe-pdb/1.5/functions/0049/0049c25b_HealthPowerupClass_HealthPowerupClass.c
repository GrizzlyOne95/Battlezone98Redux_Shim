/*
 * Entry: 0049c25b
 * Name: HealthPowerupClass::HealthPowerupClass
 * Namespace: HealthPowerupClass
 * Signature: HealthPowerupClass * HealthPowerupClass(HealthPowerupClass * this, HealthPowerupClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HealthPowerupClass * __thiscall
HealthPowerupClass::HealthPowerupClass
          (HealthPowerupClass *this,HealthPowerupClass *param_1,long64 param_2)

{
  HealthPowerupClass *pHVar1;
  undefined4 unaff_EDI;
  
  pHVar1 = param_1;
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x970ddb87,0x6b176fda,&this->healthUp,pHVar1->healthUp);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
