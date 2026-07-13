/*
 * Entry: 004be44e
 * Name: SmokeEffect::AddEmitter
 * Namespace: SmokeEffect
 * Signature: SmokeEmitter * AddEmitter(SmokeEffect * this, int param_1, int param_2, float param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SmokeEmitter * __thiscall
SmokeEffect::AddEmitter
          (SmokeEffect *this,int param_1,int param_2,float param_3,float param_4,float param_5)

{
  SmokeEmitter *pSVar1;
  SmokeEmitter *pSVar2;
  
  pSVar1 = this->emitterLast;
  for (pSVar2 = this->emitterFirst; (pSVar2 < pSVar1 && (pSVar2->sprite != 0)); pSVar2 = pSVar2 + 1)
  {
  }
  if (pSVar2 == pSVar1) {
    this->emitterLast = pSVar1 + 1;
  }
  pSVar2->rate = param_3;
  pSVar2->sprite = param_1;
  pSVar2->radius = param_4;
  pSVar2->frames = param_2;
  pSVar2->scale = ((param_5 - 1.0) * param_3 * param_4) / (float)param_2;
  return pSVar2;
}
