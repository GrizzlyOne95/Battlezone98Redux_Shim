/*
 * Entry: 0052e45b
 * Name: ExplosionFeature::Submit
 * Namespace: ExplosionFeature
 * Signature: void Submit(ExplosionFeature * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExplosionFeature::Submit(ExplosionFeature *this,CAMERA *param_1)

{
  Explosion::SubmitAll(param_1);
  return;
}
