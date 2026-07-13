/*
 * Entry: 0057209c
 * Name: AnimButton::`scalar_deleting_destructor'
 * Namespace: AnimButton
 * Signature: void * `scalar_deleting_destructor'(AnimButton * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AnimButton::_scalar_deleting_destructor_(AnimButton *this,uint param_1)

{
  ~AnimButton(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
