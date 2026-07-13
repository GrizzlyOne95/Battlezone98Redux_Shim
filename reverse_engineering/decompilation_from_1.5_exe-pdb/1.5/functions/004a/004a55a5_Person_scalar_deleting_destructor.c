/*
 * Entry: 004a55a5
 * Name: Person::`scalar_deleting_destructor'
 * Namespace: Person
 * Signature: void * `scalar_deleting_destructor'(Person * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Person::_scalar_deleting_destructor_(Person *this,uint param_1)

{
  ~Person(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
