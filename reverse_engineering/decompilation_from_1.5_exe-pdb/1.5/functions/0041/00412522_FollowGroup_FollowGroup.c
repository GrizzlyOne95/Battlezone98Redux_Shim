/*
 * Entry: 00412522
 * Name: FollowGroup::FollowGroup
 * Namespace: FollowGroup
 * Signature: FollowGroup * FollowGroup(FollowGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowGroup * __thiscall FollowGroup::FollowGroup(FollowGroup *this)

{
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::
  list<FollowerInfo,std::allocator<FollowerInfo>_>(&this->followers);
  return this;
}
