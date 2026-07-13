/*
 * Entry: 0047bee6
 * Name: AnimBuilding::AnimBuilding
 * Namespace: AnimBuilding
 * Signature: AnimBuilding * AnimBuilding(AnimBuilding * this, _OBJ76 * param_1, AnimBuildingClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimBuilding * __thiscall
AnimBuilding::AnimBuilding(AnimBuilding *this,_OBJ76 *param_1,AnimBuildingClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  AnimObj_Start((void *)this->_padding_,4,&this->animHandle);
  return this;
}
