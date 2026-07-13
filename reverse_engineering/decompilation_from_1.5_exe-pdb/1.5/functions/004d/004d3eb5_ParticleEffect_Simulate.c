/*
 * Entry: 004d3eb5
 * Name: ParticleEffect::Simulate
 * Namespace: ParticleEffect
 * Signature: void Simulate(ParticleEffect * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ParticleEffect::Simulate(ParticleEffect *this,float param_1)

{
  VECTOR_3D *pVVar1;
  Particle *pPVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  VECTOR_3D_LONG VVar6;
  int iVar7;
  VECTOR_3D local_1c;
  uint local_10;
  ParticleEffect *local_c;
  float local_8;
  
  local_10 = this->indexFirst;
  local_c = this;
LAB_004d4034:
  do {
    if (local_10 == this->indexLast) {
      return;
    }
    pPVar2 = this->particleList + local_10;
    local_10 = local_10 + 1;
    if (0xff < local_10) {
      local_10 = 0;
    }
    fVar4 = param_1 + pPVar2->time;
    pPVar2->time = fVar4;
    if (this->frameDelay < fVar4) {
      fVar3 = this->frameDelay;
      pPVar2->frame = pPVar2->frame + 1;
      pPVar2->time = fVar4 - fVar3;
      if (this->particleFrames <= pPVar2->frame) {
        this->indexFirst = this->indexFirst + 1;
        if (0xff < (uint)this->indexFirst) {
          this->indexFirst = 0;
        }
        goto LAB_004d4034;
      }
    }
    fVar4 = (pPVar2->pos).x;
    (pPVar2->vel).y = (pPVar2->vel).y - param_1 * 9.8;
    local_8 = param_1;
    VVar6.y = (double)(pPVar2->pos).y;
    VVar6.x = (double)fVar4;
    VVar6.z = (double)(pPVar2->pos).z;
    iVar7 = Terrain_GetIntersection(VVar6,pPVar2->vel,&local_8,&local_1c);
    if (iVar7 == 0) {
      (pPVar2->pos).x = param_1 * (pPVar2->vel).x + (pPVar2->pos).x;
      (pPVar2->pos).y = (pPVar2->vel).y * param_1 + (pPVar2->pos).y;
      fVar4 = (pPVar2->vel).z * param_1;
    }
    else {
      pVVar1 = &pPVar2->vel;
      (pPVar2->pos).x = local_8 * pVVar1->x + (pPVar2->pos).x;
      (pPVar2->pos).y = (pPVar2->vel).y * local_8 + (pPVar2->pos).y;
      (pPVar2->pos).z = (pPVar2->vel).z * local_8 + (pPVar2->pos).z;
      fVar4 = local_1c.x * pVVar1->x + (pPVar2->vel).z * local_1c.z + (pPVar2->vel).y * local_1c.y;
      fVar5 = pVVar1->x * 0.5 - local_1c.x * fVar4;
      pVVar1->x = fVar5;
      fVar3 = (pPVar2->vel).y * 0.5 - local_1c.y * fVar4;
      (pPVar2->vel).y = fVar3;
      fVar4 = (pPVar2->vel).z * 0.5 - local_1c.z * fVar4;
      (pPVar2->vel).z = fVar4;
      local_8 = param_1 - local_8;
      (pPVar2->pos).x = local_8 * fVar5 + (pPVar2->pos).x;
      (pPVar2->pos).y = local_8 * fVar3 + (pPVar2->pos).y;
      fVar4 = fVar4 * local_8;
    }
    (pPVar2->pos).z = fVar4 + (pPVar2->pos).z;
    this = local_c;
  } while( true );
}
