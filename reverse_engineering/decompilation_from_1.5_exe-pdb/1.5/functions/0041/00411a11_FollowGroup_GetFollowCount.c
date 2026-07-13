/*
 * Entry: 00411a11
 * Name: FollowGroup::GetFollowCount
 * Namespace: FollowGroup
 * Signature: int GetFollowCount(FollowGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall FollowGroup::GetFollowCount(FollowGroup *this)

{
  return (this->followers)._Mysize;
}
