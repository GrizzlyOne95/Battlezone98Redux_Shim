/*
 * Entry: 005cc351
 * Name: `dynamic_initializer_for_'remoteDetonatorClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'remoteDetonatorClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__remoteDetonatorClass__(void)

{
  RemoteDetonatorClass::RemoteDetonatorClass(&remoteDetonatorClass);
  atexit(_dynamic_atexit_destructor_for__remoteDetonatorClass__);
  return;
}
