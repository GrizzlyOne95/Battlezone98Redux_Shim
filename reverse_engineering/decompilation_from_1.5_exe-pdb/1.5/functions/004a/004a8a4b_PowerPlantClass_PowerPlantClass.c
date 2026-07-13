/*
 * Entry: 004a8a4b
 * Name: PowerPlantClass::PowerPlantClass
 * Namespace: PowerPlantClass
 * Signature: PowerPlantClass * PowerPlantClass(PowerPlantClass * this, PowerPlantClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlantClass * __thiscall
PowerPlantClass::PowerPlantClass(PowerPlantClass *this,PowerPlantClass *param_1,long64 param_2)

{
  PowerPlantClass *pPVar1;
  undefined4 unaff_EDI;
  
  pPVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xfccd89cd,0x2fb89be4,&this->powerRadius,
                   pPVar1->powerRadius);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
