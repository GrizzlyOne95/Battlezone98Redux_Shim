/*
 * Entry: 005cb764
 * Name: `dynamic_initializer_for_'chunkEffect''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'chunkEffect''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__chunkEffect__(void)

{
  GameFeature::GameFeature((GameFeature *)&chunkEffect);
  chunkEffect._padding_ = (int)&ChunkEffect::_vftable_;
  atexit(_dynamic_atexit_destructor_for__chunkEffect__);
  return;
}
