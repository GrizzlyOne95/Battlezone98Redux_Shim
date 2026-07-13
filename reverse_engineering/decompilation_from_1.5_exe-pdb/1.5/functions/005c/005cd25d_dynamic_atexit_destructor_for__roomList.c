/*
 * Entry: 005cd25d
 * Name: `dynamic_atexit_destructor_for_'roomList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'roomList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__roomList__(void)

{
  SessionList::~SessionList(&roomList);
  return;
}
