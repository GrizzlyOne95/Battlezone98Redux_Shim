/*
 * Entry: 0040dcb4
 * Name: ArtilleryFriend::`scalar_deleting_destructor'
 * Namespace: ArtilleryFriend
 * Signature: void * `scalar_deleting_destructor'(ArtilleryFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ArtilleryFriend::_scalar_deleting_destructor_(ArtilleryFriend *this,uint param_1)

{
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
