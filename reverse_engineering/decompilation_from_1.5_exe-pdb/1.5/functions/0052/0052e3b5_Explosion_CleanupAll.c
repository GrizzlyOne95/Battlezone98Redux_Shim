/*
 * Entry: 0052e3b5
 * Name: Explosion::CleanupAll
 * Namespace: Explosion
 * Signature: void CleanupAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Explosion::CleanupAll(void)

{
  Explosion **ppEVar1;
  
  while (explosionList._Mysize != 0) {
    ppEVar1 = std::list<Explosion_*,std::allocator<Explosion_*>_>::back(&explosionList);
    (**(code **)((*ppEVar1)->_padding_ + 0xc))();
  }
  return;
}
