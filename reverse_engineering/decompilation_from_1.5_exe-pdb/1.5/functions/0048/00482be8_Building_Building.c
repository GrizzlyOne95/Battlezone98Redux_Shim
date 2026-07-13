/*
 * Entry: 00482be8
 * Name: Building::Building
 * Namespace: Building
 * Signature: Building * Building(Building * this, _OBJ76 * param_1, BuildingClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Building * __thiscall Building::Building(Building *this,_OBJ76 *param_1,BuildingClass *param_2)

{
  GameObject::GameObject((GameObject *)this,param_1,(GameObjectClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  if ((param_2->_padding_ == 0x74736261) && (param_2->_padding_ == 0x726f)) {
    this->_padding_ = this->_padding_;
  }
  this->soundAmbient = (_gas_object *)0x0;
  this->tempBuilding = true;
  return this;
}
