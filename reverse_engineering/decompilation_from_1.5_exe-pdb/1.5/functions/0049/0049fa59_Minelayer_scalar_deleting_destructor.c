/*
 * Entry: 0049fa59
 * Name: Minelayer::`scalar_deleting_destructor'
 * Namespace: Minelayer
 * Signature: void * `scalar_deleting_destructor'(Minelayer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Minelayer::_scalar_deleting_destructor_(Minelayer *this,uint param_1)

{
  ~Minelayer(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
