/*
 * Entry: 005c9cf1
 * Name: `dynamic_initializer_for_'FollowGroup::followGroups''
 * Namespace: `dynamic_initializer_for_'FollowGroup
 * Signature: void followGroups''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'FollowGroup::followGroups__(void)

{
  std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::
  list<FollowGroup_*,std::allocator<FollowGroup_*>_>(&FollowGroup::followGroups);
  atexit(`dynamic_atexit_destructor_for_'FollowGroup::followGroups__);
  return;
}
