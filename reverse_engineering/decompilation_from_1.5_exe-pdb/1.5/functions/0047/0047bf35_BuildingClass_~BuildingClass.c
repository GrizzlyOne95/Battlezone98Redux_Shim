/*
 * Entry: 0047bf35
 * Name: BuildingClass::~BuildingClass
 * Namespace: BuildingClass
 * Signature: void ~BuildingClass(BuildingClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BuildingClass::~BuildingClass(BuildingClass *this)

{
  this->_padding_ = (int)&GameObjectClass::_vftable_;
  if ((void *)this->_padding_ != (void *)0x0) {
    operator_delete__((void *)this->_padding_);
  }
  Attachable::~Attachable((Attachable *)this);
  return;
}
