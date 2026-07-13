/*
 * Entry: 00489eab
 * Name: Crater::Crater
 * Namespace: Crater
 * Signature: Crater * Crater(Crater * this, float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Crater * __thiscall Crater::Crater(Crater *this,float param_1,float param_2,float param_3)

{
  DistributedObject::DistributedObject((DistributedObject *)this);
  this->fx = param_1;
  this->_padding_ = (int)&_vftable_;
  this->dug = false;
  this->fz = param_2;
  this->dy = param_3;
  return this;
}
