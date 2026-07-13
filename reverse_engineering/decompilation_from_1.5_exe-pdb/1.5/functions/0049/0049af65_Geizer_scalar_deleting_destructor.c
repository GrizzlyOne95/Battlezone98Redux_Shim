/*
 * Entry: 0049af65
 * Name: Geizer::`scalar_deleting_destructor'
 * Namespace: Geizer
 * Signature: void * `scalar_deleting_destructor'(Geizer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Geizer::_scalar_deleting_destructor_(Geizer *this,uint param_1)

{
  ~Geizer(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
