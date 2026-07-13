/*
 * Entry: 0047dd44
 * Name: APC::`scalar_deleting_destructor'
 * Namespace: APC
 * Signature: void * `scalar_deleting_destructor'(APC * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall APC::_scalar_deleting_destructor_(APC *this,uint param_1)

{
  ~APC(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
