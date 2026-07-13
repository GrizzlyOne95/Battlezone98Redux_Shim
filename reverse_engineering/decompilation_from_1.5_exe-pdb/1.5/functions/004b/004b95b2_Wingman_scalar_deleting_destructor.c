/*
 * Entry: 004b95b2
 * Name: Wingman::`scalar_deleting_destructor'
 * Namespace: Wingman
 * Signature: void * `scalar_deleting_destructor'(Wingman * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Wingman::_scalar_deleting_destructor_(Wingman *this,uint param_1)

{
  HoverCraft::~HoverCraft((HoverCraft *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
