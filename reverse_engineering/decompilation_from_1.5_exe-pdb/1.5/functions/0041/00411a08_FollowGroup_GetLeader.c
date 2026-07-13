/*
 * Entry: 00411a08
 * Name: FollowGroup::GetLeader
 * Namespace: FollowGroup
 * Signature: GameObject * GetLeader(FollowGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall FollowGroup::GetLeader(FollowGroup *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(this->leader);
  return pGVar1;
}
