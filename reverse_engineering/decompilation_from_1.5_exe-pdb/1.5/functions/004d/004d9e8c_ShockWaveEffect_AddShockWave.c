/*
 * Entry: 004d9e8c
 * Name: ShockWaveEffect::AddShockWave
 * Namespace: ShockWaveEffect
 * Signature: void AddShockWave(ShockWaveEffect * this, VECTOR_3D * param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ShockWaveEffect::AddShockWave
          (ShockWaveEffect *this,VECTOR_3D *param_1,float param_2,float param_3,float param_4)

{
  ShockWave *pSVar1;
  uint uVar2;
  float fVar3;
  
  uVar2 = this->shockwaveCount;
  if (uVar2 < 0x20) {
    pSVar1 = this->shockwaveList + uVar2;
    this->shockwaveCount = uVar2 + 1;
    (pSVar1->pos).x = param_1->x;
    (pSVar1->pos).y = param_1->y;
    (pSVar1->pos).z = param_1->z;
    pSVar1->outerRad = param_2;
    pSVar1->innerRad = param_2 * 0.5;
    fVar3 = 1.0 / param_4;
    pSVar1->outerVel = (param_3 - param_2) * fVar3;
    pSVar1->innerVel = (param_3 - param_2 * 0.5) * fVar3;
    pSVar1->frameRate = fVar3 * 16.0;
    pSVar1->frameIndex = (float)this->shockwaveIndex;
  }
  return;
}
