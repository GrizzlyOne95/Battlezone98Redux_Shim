/*
 * Entry: 0047e94d
 * Name: Armory::`scalar_deleting_destructor'
 * Namespace: Armory
 * Signature: void * `scalar_deleting_destructor'(Armory * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Armory::_scalar_deleting_destructor_(Armory *this,uint param_1)

{
  ~Armory(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
