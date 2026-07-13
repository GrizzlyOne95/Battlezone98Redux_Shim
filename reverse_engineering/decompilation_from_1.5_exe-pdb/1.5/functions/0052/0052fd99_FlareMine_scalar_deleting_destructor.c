/*
 * Entry: 0052fd99
 * Name: FlareMine::`scalar_deleting_destructor'
 * Namespace: FlareMine
 * Signature: void * `scalar_deleting_destructor'(FlareMine * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FlareMine::_scalar_deleting_destructor_(FlareMine *this,uint param_1)

{
  ~FlareMine(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
