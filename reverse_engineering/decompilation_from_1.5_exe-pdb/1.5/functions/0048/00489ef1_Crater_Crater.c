/*
 * Entry: 00489ef1
 * Name: Crater::Crater
 * Namespace: Crater
 * Signature: Crater * Crater(Crater * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Crater * __thiscall Crater::Crater(Crater *this)

{
  DistributedObject::DistributedObject((DistributedObject *)this);
  this->fx = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->fz = 0.0;
  this->dug = false;
  this->dy = 0.0;
  return this;
}
