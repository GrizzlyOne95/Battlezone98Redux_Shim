/*
 * Entry: 005c9ac0
 * Name: `dynamic_initializer_for_'AiPath::pathList''
 * Namespace: `dynamic_initializer_for_'AiPath
 * Signature: void pathList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'AiPath::pathList__(void)

{
  std::list<AiPath_*,std::allocator<AiPath_*>_>::list<AiPath_*,std::allocator<AiPath_*>_>
            (&AiPath::pathList);
  atexit(`dynamic_atexit_destructor_for_'AiPath::pathList__);
  return;
}
