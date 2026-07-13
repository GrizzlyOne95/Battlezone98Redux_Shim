/*
 * Entry: 004ae891
 * Name: Scavenger::`scalar_deleting_destructor'
 * Namespace: Scavenger
 * Signature: void * `scalar_deleting_destructor'(Scavenger * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Scavenger::_scalar_deleting_destructor_(Scavenger *this,uint param_1)

{
  ~Scavenger(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
