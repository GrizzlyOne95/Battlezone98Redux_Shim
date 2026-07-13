/*
 * Entry: 005317e9
 * Name: MagnetMine::`scalar_deleting_destructor'
 * Namespace: MagnetMine
 * Signature: void * `scalar_deleting_destructor'(MagnetMine * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MagnetMine::_scalar_deleting_destructor_(MagnetMine *this,uint param_1)

{
  ~MagnetMine(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
