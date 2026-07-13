/*
 * Entry: 00535ef5
 * Name: PlanarExplosion::Simulate
 * Namespace: PlanarExplosion
 * Signature: void Simulate(PlanarExplosion * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlanarExplosion::Simulate(PlanarExplosion *this,float param_1)

{
  float *pfVar1;
  
  pfVar1 = (float *)(this->_padding_ + 0xd4);
  *pfVar1 = this->velocRadial * param_1 + *pfVar1;
  Explosion::Simulate((Explosion *)this,param_1);
  return;
}
