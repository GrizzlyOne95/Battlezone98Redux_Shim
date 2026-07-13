/*
 * Entry: 004d9c8c
 * Name: ScrapGauge::`scalar_deleting_destructor'
 * Namespace: ScrapGauge
 * Signature: void * `scalar_deleting_destructor'(ScrapGauge * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScrapGauge::_scalar_deleting_destructor_(ScrapGauge *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
