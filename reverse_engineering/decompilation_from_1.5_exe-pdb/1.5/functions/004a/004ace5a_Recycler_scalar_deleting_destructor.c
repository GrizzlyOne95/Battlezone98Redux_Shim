/*
 * Entry: 004ace5a
 * Name: Recycler::`scalar_deleting_destructor'
 * Namespace: Recycler
 * Signature: void * `scalar_deleting_destructor'(Recycler * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Recycler::_scalar_deleting_destructor_(Recycler *this,uint param_1)

{
  ~Recycler(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
