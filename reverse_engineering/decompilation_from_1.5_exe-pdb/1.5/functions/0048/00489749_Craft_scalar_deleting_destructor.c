/*
 * Entry: 00489749
 * Name: Craft::`scalar_deleting_destructor'
 * Namespace: Craft
 * Signature: void * `scalar_deleting_destructor'(Craft * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Craft::_scalar_deleting_destructor_(Craft *this,uint param_1)

{
  ~Craft(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
