/*
 * Entry: 0049d01c
 * Name: HoverCraft::`scalar_deleting_destructor'
 * Namespace: HoverCraft
 * Signature: void * `scalar_deleting_destructor'(HoverCraft * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HoverCraft::_scalar_deleting_destructor_(HoverCraft *this,uint param_1)

{
  ~HoverCraft(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
