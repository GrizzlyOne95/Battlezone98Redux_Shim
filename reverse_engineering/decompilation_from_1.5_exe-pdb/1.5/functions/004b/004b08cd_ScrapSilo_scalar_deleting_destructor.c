/*
 * Entry: 004b08cd
 * Name: ScrapSilo::`scalar_deleting_destructor'
 * Namespace: ScrapSilo
 * Signature: void * `scalar_deleting_destructor'(ScrapSilo * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScrapSilo::_scalar_deleting_destructor_(ScrapSilo *this,uint param_1)

{
  ~ScrapSilo(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
