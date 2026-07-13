/*
 * Entry: 004af048
 * Name: ScavengerClass::`scalar_deleting_destructor'
 * Namespace: ScavengerClass
 * Signature: void * `scalar_deleting_destructor'(ScavengerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScavengerClass::_scalar_deleting_destructor_(ScavengerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
