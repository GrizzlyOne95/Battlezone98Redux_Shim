/*
 * Entry: 0052e44a
 * Name: ExplosionFeature::Simulate
 * Namespace: ExplosionFeature
 * Signature: void Simulate(ExplosionFeature * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExplosionFeature::Simulate(ExplosionFeature *this,float param_1)

{
  Explosion::SimulateAll(param_1);
  return;
}
