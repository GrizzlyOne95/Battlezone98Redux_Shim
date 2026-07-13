/*
 * Entry: 00403b5b
 * Name: AiPath::`scalar_deleting_destructor'
 * Namespace: AiPath
 * Signature: void * `scalar_deleting_destructor'(AiPath * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AiPath::_scalar_deleting_destructor_(AiPath *this,uint param_1)

{
  ~AiPath(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
