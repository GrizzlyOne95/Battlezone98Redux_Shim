/*
 * Entry: 0048359e
 * Name: BuildingClass::BuildingClass
 * Namespace: BuildingClass
 * Signature: BuildingClass * BuildingClass(BuildingClass * this, ulong param_1, char * param_2, OBJECT_CLASS_T param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BuildingClass * __thiscall
BuildingClass::BuildingClass(BuildingClass *this,ulong param_1,char *param_2,OBJECT_CLASS_T param_3)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)this);
  this->_padding_ = param_1;
  this->_padding_ = (int)param_2;
  this->_padding_ = param_3;
  this->_padding_ = (int)&_vftable_;
  this->soundAmbient[0] = '\0';
  return this;
}
