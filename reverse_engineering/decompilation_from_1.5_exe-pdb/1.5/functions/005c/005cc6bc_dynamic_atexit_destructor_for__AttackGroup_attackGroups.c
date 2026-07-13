/*
 * Entry: 005cc6bc
 * Name: `dynamic_atexit_destructor_for_'AttackGroup::attackGroups''
 * Namespace: `dynamic_atexit_destructor_for_'AttackGroup
 * Signature: void attackGroups''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'AttackGroup::attackGroups__(void)

{
  std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Tidy(&AttackGroup::attackGroups);
  operator_delete((void *)AttackGroup::attackGroups._padding_);
  return;
}
