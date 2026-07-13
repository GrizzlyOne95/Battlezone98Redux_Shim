/*
 * Entry: 005ca893
 * Name: `dynamic_initializer_for_'msgMgr''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'msgMgr''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__msgMgr__(void)

{
  AudioMessageMgr::AudioMessageMgr(&msgMgr);
  atexit(_dynamic_atexit_destructor_for__msgMgr__);
  return;
}
