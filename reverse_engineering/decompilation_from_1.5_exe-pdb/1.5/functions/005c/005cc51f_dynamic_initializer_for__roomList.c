/*
 * Entry: 005cc51f
 * Name: `dynamic_initializer_for_'roomList''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'roomList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__roomList__(void)

{
  SessionList::SessionList(&roomList);
  atexit(_dynamic_atexit_destructor_for__roomList__);
  return;
}
