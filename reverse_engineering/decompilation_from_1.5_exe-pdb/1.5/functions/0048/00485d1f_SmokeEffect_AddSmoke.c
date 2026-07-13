/*
 * Entry: 00485d1f
 * Name: SmokeEffect::AddSmoke
 * Namespace: SmokeEffect
 * Signature: void AddSmoke(SmokeEffect * this, SmokeEmitter * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
SmokeEffect::AddSmoke
          (SmokeEffect *this,SmokeEmitter *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,
          float param_4)

{
  SmokePuff **ppSVar1;
  SmokePuff *pSVar2;
  float fVar3;
  float fVar4;
  
  ppSVar1 = &this->puffLast;
  pSVar2 = *ppSVar1;
  if (pSVar2 < ppSVar1) {
    fVar3 = param_4 * param_1->rate + (float)param_1->sprite;
    fVar4 = (float)(param_1->frames + param_1->sprite);
    if (fVar3 < fVar4) {
      *ppSVar1 = pSVar2 + 1;
      (pSVar2->pos).x = param_2->x;
      (pSVar2->pos).y = param_2->y;
      (pSVar2->pos).z = param_2->z;
      (pSVar2->vel).x = param_3->x;
      (pSVar2->vel).y = param_3->y;
      (pSVar2->vel).z = param_3->z;
      pSVar2->frame = fVar3;
      pSVar2->finish = fVar4;
      pSVar2->rate = param_1->rate;
      pSVar2->radius = param_1->scale * param_4 + param_1->radius;
      pSVar2->scale = param_1->scale;
    }
  }
  return;
}
