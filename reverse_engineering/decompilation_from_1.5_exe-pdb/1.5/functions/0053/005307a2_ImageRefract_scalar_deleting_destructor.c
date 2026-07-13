/*
 * Entry: 005307a2
 * Name: ImageRefract::`scalar_deleting_destructor'
 * Namespace: ImageRefract
 * Signature: void * `scalar_deleting_destructor'(ImageRefract * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ImageRefract::_scalar_deleting_destructor_(ImageRefract *this,uint param_1)

{
  ~ImageRefract(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
