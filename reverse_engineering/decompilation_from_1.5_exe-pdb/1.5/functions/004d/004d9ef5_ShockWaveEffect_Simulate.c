/*
 * Entry: 004d9ef5
 * Name: ShockWaveEffect::Simulate
 * Namespace: ShockWaveEffect
 * Signature: void Simulate(ShockWaveEffect * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShockWaveEffect::Simulate(ShockWaveEffect *this,float param_1)

{
  float fVar1;
  int iVar2;
  ShockWave *pSVar3;
  ShockWave *pSVar4;
  ShockWave *pSVar5;
  int local_8;
  
  local_8 = 0;
  if (0 < this->shockwaveCount) {
    pSVar3 = this->shockwaveList;
    do {
      fVar1 = pSVar3->frameRate * param_1 + pSVar3->frameIndex;
      pSVar3->frameIndex = fVar1;
      if ((float)this->shockwaveFrames < fVar1 == ((float)this->shockwaveFrames == fVar1)) {
        pSVar3->outerRad = pSVar3->outerVel * param_1 + pSVar3->outerRad;
        pSVar3->innerRad = pSVar3->innerVel * param_1 + pSVar3->innerRad;
      }
      else {
        this->shockwaveCount = this->shockwaveCount + -1;
        local_8 = local_8 + -1;
        pSVar4 = this->shockwaveList + this->shockwaveCount;
        pSVar5 = pSVar3;
        for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
          (pSVar5->pos).x = (pSVar4->pos).x;
          pSVar4 = (ShockWave *)&(pSVar4->pos).y;
          pSVar5 = (ShockWave *)&(pSVar5->pos).y;
        }
        pSVar3 = pSVar3 + -1;
      }
      local_8 = local_8 + 1;
      pSVar3 = pSVar3 + 1;
    } while (local_8 < this->shockwaveCount);
  }
  return;
}
