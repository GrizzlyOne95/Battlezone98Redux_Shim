/*
 * Entry: 005cc957
 * Name: `dynamic_atexit_destructor_for_'GameObjectClass::classList''
 * Namespace: `dynamic_atexit_destructor_for_'GameObjectClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'GameObjectClass::classList__(void)

{
  std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Tidy
            (&GameObjectClass::classList);
  operator_delete((void *)GameObjectClass::classList._padding_);
  return;
}
