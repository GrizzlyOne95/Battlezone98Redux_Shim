/*
 * Entry: 004da22f
 * Name: SmokeEffect::Simulate
 * Namespace: SmokeEffect
 * Signature: void Simulate(SmokeEffect * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SmokeEffect::Simulate(SmokeEffect *this,float param_1)

{
  float fVar1;
  int iVar2;
  SmokePuff *pSVar3;
  SmokePuff *pSVar4;
  SmokePuff *pSVar5;
  
  pSVar3 = this->puffFirst;
  if (pSVar3 < this->puffLast) {
    do {
      fVar1 = pSVar3->rate * param_1 + pSVar3->frame;
      pSVar3->frame = fVar1;
      if (fVar1 < pSVar3->finish) {
        pSVar3->radius = pSVar3->scale * param_1 + pSVar3->radius;
        (pSVar3->pos).x = (pSVar3->vel).x * param_1 + (pSVar3->pos).x;
        (pSVar3->pos).y = (pSVar3->vel).y * param_1 + (pSVar3->pos).y;
        (pSVar3->pos).z = (pSVar3->vel).z * param_1 + (pSVar3->pos).z;
      }
      else {
        this->puffLast = this->puffLast + -1;
        pSVar4 = this->puffLast;
        pSVar5 = pSVar3;
        for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
          (pSVar5->pos).x = (pSVar4->pos).x;
          pSVar4 = (SmokePuff *)&(pSVar4->pos).y;
          pSVar5 = (SmokePuff *)&(pSVar5->pos).y;
        }
        pSVar3 = pSVar3 + -1;
      }
      pSVar3 = pSVar3 + 1;
    } while (pSVar3 < this->puffLast);
  }
  return;
}
