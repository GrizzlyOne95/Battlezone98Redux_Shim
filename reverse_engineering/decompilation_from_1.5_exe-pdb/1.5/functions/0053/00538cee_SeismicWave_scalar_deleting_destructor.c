/*
 * Entry: 00538cee
 * Name: SeismicWave::`scalar_deleting_destructor'
 * Namespace: SeismicWave
 * Signature: void * `scalar_deleting_destructor'(SeismicWave * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SeismicWave::_scalar_deleting_destructor_(SeismicWave *this,uint param_1)

{
  ~SeismicWave(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
