/*
 * Entry: 005c9c04
 * Name: `dynamic_initializer_for_'AttackGroup::attackGroups''
 * Namespace: `dynamic_initializer_for_'AttackGroup
 * Signature: void attackGroups''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'AttackGroup::attackGroups__(void)

{
  std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::
  list<AttackGroup_*,std::allocator<AttackGroup_*>_>(&AttackGroup::attackGroups);
  atexit(`dynamic_atexit_destructor_for_'AttackGroup::attackGroups__);
  return;
}
