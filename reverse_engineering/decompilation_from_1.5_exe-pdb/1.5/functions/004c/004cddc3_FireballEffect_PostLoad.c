/*
 * Entry: 004cddc3
 * Name: FireballEffect::PostLoad
 * Namespace: FireballEffect
 * Signature: void PostLoad(FireballEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FireballEffect::PostLoad(FireballEffect *this)

{
  SmokeEmitter *pSVar1;
  
  pSVar1 = SmokeEffect::AddEmitter
                     (&smokeEffect,this->smokeTexture,this->smokeFrames,
                      (float)this->smokeFrames / this->smokeLifespan,this->smokeRadius,
                      this->smokeScale);
  this->smokeEmitter = pSVar1;
  return;
}
