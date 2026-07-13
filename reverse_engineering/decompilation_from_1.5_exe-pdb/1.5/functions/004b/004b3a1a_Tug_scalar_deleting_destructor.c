/*
 * Entry: 004b3a1a
 * Name: Tug::`scalar_deleting_destructor'
 * Namespace: Tug
 * Signature: void * `scalar_deleting_destructor'(Tug * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Tug::_scalar_deleting_destructor_(Tug *this,uint param_1)

{
  ~Tug(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
