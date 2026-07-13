/*
 * Entry: 004cde10
 * Name: FireballEffect::AddFireball
 * Namespace: FireballEffect
 * Signature: void AddFireball(FireballEffect * this, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
FireballEffect::AddFireball(FireballEffect *this,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  Fireball *pFVar1;
  
  pFVar1 = this->fireballList + this->indexLast;
  (pFVar1->pos).x = param_1->x;
  (pFVar1->pos).y = param_1->y;
  (pFVar1->pos).z = param_1->z;
  (pFVar1->vel).x = param_2->x;
  (pFVar1->vel).y = param_2->y;
  (pFVar1->vel).z = param_2->z;
  pFVar1->frame = (float)this->fireballTexture;
  pFVar1->emit = 0.0;
  pFVar1->radius = this->fireballRadius;
  this->indexLast = this->indexLast + 1;
  if (0x1f < (uint)this->indexLast) {
    this->indexLast = 0;
  }
  return;
}
