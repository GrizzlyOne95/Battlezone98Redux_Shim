/*
 * Entry: 004c9083
 * Name: DustEffect::Simulate
 * Namespace: DustEffect
 * Signature: void Simulate(DustEffect * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DustEffect::Simulate(DustEffect *this,float param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  DustPuff *pDVar4;
  DustPuff *pDVar5;
  DustPuff *pDVar6;
  
  pDVar4 = this->puffFirst;
  if (pDVar4 < this->puffLast) {
    do {
      fVar1 = this->dustRate * param_1 + pDVar4->frame;
      pDVar4->frame = fVar1;
      fVar2 = (float)(this->dustTexture + this->dustFrames);
      if (fVar2 < fVar1 == (fVar2 == fVar1)) {
        pDVar4->radius = this->dustScale * param_1 + pDVar4->radius;
        (pDVar4->pos).x = (pDVar4->vel).x * param_1 + (pDVar4->pos).x;
        (pDVar4->pos).y = (pDVar4->vel).y * param_1 + (pDVar4->pos).y;
        (pDVar4->pos).z = (pDVar4->vel).z * param_1 + (pDVar4->pos).z;
      }
      else {
        this->puffLast = this->puffLast + -1;
        pDVar5 = this->puffLast;
        pDVar6 = pDVar4;
        for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
          (pDVar6->pos).x = (pDVar5->pos).x;
          pDVar5 = (DustPuff *)&(pDVar5->pos).y;
          pDVar6 = (DustPuff *)&(pDVar6->pos).y;
        }
        pDVar4 = pDVar4 + -1;
      }
      pDVar4 = pDVar4 + 1;
    } while (pDVar4 < this->puffLast);
  }
  return;
}
