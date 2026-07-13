/*
 * Entry: 005cc038
 * Name: `dynamic_initializer_for_'objectLobberClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'objectLobberClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__objectLobberClass__(void)

{
  ObjectLobberClass::ObjectLobberClass(&objectLobberClass);
  atexit(_dynamic_atexit_destructor_for__objectLobberClass__);
  return;
}
