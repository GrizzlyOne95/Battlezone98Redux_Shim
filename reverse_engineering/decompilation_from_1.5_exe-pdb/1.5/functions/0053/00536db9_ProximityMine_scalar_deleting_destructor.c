/*
 * Entry: 00536db9
 * Name: ProximityMine::`scalar_deleting_destructor'
 * Namespace: ProximityMine
 * Signature: void * `scalar_deleting_destructor'(ProximityMine * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ProximityMine::_scalar_deleting_destructor_(ProximityMine *this,uint param_1)

{
  ~ProximityMine(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
