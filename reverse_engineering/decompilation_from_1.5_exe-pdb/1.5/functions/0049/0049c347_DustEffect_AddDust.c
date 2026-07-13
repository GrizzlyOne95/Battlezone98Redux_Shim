/*
 * Entry: 0049c347
 * Name: DustEffect::AddDust
 * Namespace: DustEffect
 * Signature: void AddDust(DustEffect * this, VECTOR_3D * param_1, VECTOR_3D * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
DustEffect::AddDust(DustEffect *this,VECTOR_3D *param_1,VECTOR_3D *param_2,float param_3)

{
  DustPuff **ppDVar1;
  DustPuff *pDVar2;
  float fVar3;
  
  ppDVar1 = &this->puffLast;
  pDVar2 = *ppDVar1;
  if ((pDVar2 < ppDVar1) &&
     (fVar3 = this->dustRate * param_3 + (float)this->dustTexture,
     fVar3 < (float)(this->dustFrames + this->dustTexture))) {
    *ppDVar1 = pDVar2 + 1;
    (pDVar2->pos).x = param_1->x;
    (pDVar2->pos).y = param_1->y;
    (pDVar2->pos).z = param_1->z;
    (pDVar2->vel).x = param_2->x;
    (pDVar2->vel).y = param_2->y;
    (pDVar2->vel).z = param_2->z;
    pDVar2->frame = fVar3;
    pDVar2->radius = this->dustRadius;
  }
  return;
}
