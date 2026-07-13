/*
 * Entry: 00482588
 * Name: Barracks::`scalar_deleting_destructor'
 * Namespace: Barracks
 * Signature: void * `scalar_deleting_destructor'(Barracks * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Barracks::_scalar_deleting_destructor_(Barracks *this,uint param_1)

{
  ~Barracks(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
