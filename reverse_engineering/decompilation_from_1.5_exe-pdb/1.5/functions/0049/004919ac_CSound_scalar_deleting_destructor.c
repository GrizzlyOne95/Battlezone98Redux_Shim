/*
 * Entry: 004919ac
 * Name: CSound::`scalar_deleting_destructor'
 * Namespace: CSound
 * Signature: void * `scalar_deleting_destructor'(CSound * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CSound::_scalar_deleting_destructor_(CSound *this,uint param_1)

{
  ~CSound(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
