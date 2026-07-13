/*
 * Entry: 005cc6d3
 * Name: `dynamic_atexit_destructor_for_'FollowGroup::followGroups''
 * Namespace: `dynamic_atexit_destructor_for_'FollowGroup
 * Signature: void followGroups''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'FollowGroup::followGroups__(void)

{
  std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Tidy(&FollowGroup::followGroups);
  operator_delete((void *)FollowGroup::followGroups._padding_);
  return;
}
