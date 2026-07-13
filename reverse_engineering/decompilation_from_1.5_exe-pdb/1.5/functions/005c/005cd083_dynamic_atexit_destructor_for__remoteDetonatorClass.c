/*
 * Entry: 005cd083
 * Name: `dynamic_atexit_destructor_for_'remoteDetonatorClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'remoteDetonatorClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__remoteDetonatorClass__(void)

{
  remoteDetonatorClass._padding_ = (int)&RemoteDetonatorClass::_vftable_;
  MortarClass::~MortarClass((MortarClass *)&remoteDetonatorClass);
  return;
}
