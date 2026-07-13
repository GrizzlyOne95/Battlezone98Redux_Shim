/*
 * Entry: 005cc660
 * Name: `dynamic_atexit_destructor_for_'AiPath::pathList''
 * Namespace: `dynamic_atexit_destructor_for_'AiPath
 * Signature: void pathList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'AiPath::pathList__(void)

{
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Tidy(&AiPath::pathList);
  operator_delete((void *)AiPath::pathList._padding_);
  return;
}
