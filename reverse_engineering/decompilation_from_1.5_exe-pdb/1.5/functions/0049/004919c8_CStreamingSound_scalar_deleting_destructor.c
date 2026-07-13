/*
 * Entry: 004919c8
 * Name: CStreamingSound::`scalar_deleting_destructor'
 * Namespace: CStreamingSound
 * Signature: void * `scalar_deleting_destructor'(CStreamingSound * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CStreamingSound::_scalar_deleting_destructor_(CStreamingSound *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  CSound::~CSound((CSound *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
