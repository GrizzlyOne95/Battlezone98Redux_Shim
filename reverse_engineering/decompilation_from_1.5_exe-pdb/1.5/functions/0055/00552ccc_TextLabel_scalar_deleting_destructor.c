/*
 * Entry: 00552ccc
 * Name: TextLabel::`scalar_deleting_destructor'
 * Namespace: TextLabel
 * Signature: void * `scalar_deleting_destructor'(TextLabel * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TextLabel::_scalar_deleting_destructor_(TextLabel *this,uint param_1)

{
  ~TextLabel(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
