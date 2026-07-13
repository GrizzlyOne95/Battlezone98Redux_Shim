/*
 * Entry: 00412531
 * Name: FollowGroup::`scalar_deleting_destructor'
 * Namespace: FollowGroup
 * Signature: void * `scalar_deleting_destructor'(FollowGroup * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FollowGroup::_scalar_deleting_destructor_(FollowGroup *this,uint param_1)

{
  ~FollowGroup(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
