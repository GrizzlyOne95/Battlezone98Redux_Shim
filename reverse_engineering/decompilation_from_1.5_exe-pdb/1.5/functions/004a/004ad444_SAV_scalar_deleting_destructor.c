/*
 * Entry: 004ad444
 * Name: SAV::`scalar_deleting_destructor'
 * Namespace: SAV
 * Signature: void * `scalar_deleting_destructor'(SAV * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SAV::_scalar_deleting_destructor_(SAV *this,uint param_1)

{
  HoverCraft::~HoverCraft((HoverCraft *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
