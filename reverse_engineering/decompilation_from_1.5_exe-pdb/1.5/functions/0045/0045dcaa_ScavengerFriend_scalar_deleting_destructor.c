/*
 * Entry: 0045dcaa
 * Name: ScavengerFriend::`scalar_deleting_destructor'
 * Namespace: ScavengerFriend
 * Signature: void * `scalar_deleting_destructor'(ScavengerFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScavengerFriend::_scalar_deleting_destructor_(ScavengerFriend *this,uint param_1)

{
  ScavengerProcess::~ScavengerProcess((ScavengerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
