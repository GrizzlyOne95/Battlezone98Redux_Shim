/*
 * Entry: 00412458
 * Name: FollowGroup::~FollowGroup
 * Namespace: FollowGroup
 * Signature: void ~FollowGroup(FollowGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowGroup::~FollowGroup(FollowGroup *this)

{
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Tidy(&this->followers);
  operator_delete((void *)(this->followers)._padding_);
  return;
}
