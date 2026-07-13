/*
 * Entry: 004835f4
 * Name: BuildingClass::BuildingClass
 * Namespace: BuildingClass
 * Signature: BuildingClass * BuildingClass(BuildingClass * this, BuildingClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BuildingClass * __thiscall
BuildingClass::BuildingClass(BuildingClass *this,BuildingClass *param_1,long64 param_2)

{
  BuildingClass *pBVar1;
  undefined4 unaff_EDI;
  
  pBVar1 = param_1;
  GameObjectClass::GameObjectClass
            ((GameObjectClass *)this,(GameObjectClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x91e9360f,0xf1aad7dc,this->soundAmbient,0x10,
                   pBVar1->soundAmbient);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
