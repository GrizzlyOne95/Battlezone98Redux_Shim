/*
 * Entry: 0052e46d
 * Name: ExplosionFeature::PostRun
 * Namespace: ExplosionFeature
 * Signature: void PostRun(ExplosionFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExplosionFeature::PostRun(ExplosionFeature *this)

{
  Explosion **ppEVar1;
  
  while (Explosion::explosionList._Mysize != 0) {
    ppEVar1 = std::list<Explosion_*,std::allocator<Explosion_*>_>::back(&Explosion::explosionList);
    (**(code **)((*ppEVar1)->_padding_ + 0xc))();
  }
  return;
}
