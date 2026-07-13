/*
 * Entry: 004d3c73
 * Name: ParticleEffect::AddParticle
 * Namespace: ParticleEffect
 * Signature: void AddParticle(ParticleEffect * this, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ParticleEffect::AddParticle(ParticleEffect *this,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  Particle *pPVar1;
  float fVar2;
  
  pPVar1 = this->particleList + this->indexLast;
  (pPVar1->pos).x = param_1->x;
  (pPVar1->pos).y = param_1->y;
  (pPVar1->pos).z = param_1->z;
  (pPVar1->vel).x = param_2->x;
  (pPVar1->vel).y = param_2->y;
  (pPVar1->vel).z = param_2->z;
  fVar2 = this->initDelay;
  pPVar1->frame = 0;
  pPVar1->time = -fVar2;
  this->indexLast = this->indexLast + 1;
  if (0xff < (uint)this->indexLast) {
    this->indexLast = 0;
  }
  return;
}
