/*
 * Entry: 00538ca6
 * Name: SeismicWaveClass::`scalar_deleting_destructor'
 * Namespace: SeismicWaveClass
 * Signature: void * `scalar_deleting_destructor'(SeismicWaveClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SeismicWaveClass::_scalar_deleting_destructor_(SeismicWaveClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  OrdnanceClass::~OrdnanceClass((OrdnanceClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
