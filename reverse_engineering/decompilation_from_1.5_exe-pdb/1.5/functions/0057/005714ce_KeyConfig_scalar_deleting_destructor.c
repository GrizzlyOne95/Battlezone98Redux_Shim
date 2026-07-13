/*
 * Entry: 005714ce
 * Name: KeyConfig::`scalar_deleting_destructor'
 * Namespace: KeyConfig
 * Signature: void * `scalar_deleting_destructor'(KeyConfig * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall KeyConfig::_scalar_deleting_destructor_(KeyConfig *this,uint param_1)

{
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
