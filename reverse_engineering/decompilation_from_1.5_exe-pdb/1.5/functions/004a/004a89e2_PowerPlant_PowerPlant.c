/*
 * Entry: 004a89e2
 * Name: PowerPlant::PowerPlant
 * Namespace: PowerPlant
 * Signature: PowerPlant * PowerPlant(PowerPlant * this, _OBJ76 * param_1, PowerPlantClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant * __thiscall
PowerPlant::PowerPlant(PowerPlant *this,_OBJ76 *param_1,PowerPlantClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  param_2 = (PowerPlantClass *)this;
  std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::push_back
            (&powerPlantList,(PowerPlant **)&param_2);
  AnimObj_Start((void *)this->_padding_,4,&this->animHandle);
  return this;
}
