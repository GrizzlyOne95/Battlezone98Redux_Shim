/*
 * Entry: 004aacb2
 * Name: Producer::`scalar_deleting_destructor'
 * Namespace: Producer
 * Signature: void * `scalar_deleting_destructor'(Producer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Producer::_scalar_deleting_destructor_(Producer *this,uint param_1)

{
  ~Producer(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
