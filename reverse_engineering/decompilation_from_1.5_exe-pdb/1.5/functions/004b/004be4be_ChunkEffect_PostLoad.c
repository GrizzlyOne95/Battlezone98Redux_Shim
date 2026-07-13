/*
 * Entry: 004be4be
 * Name: ChunkEffect::PostLoad
 * Namespace: ChunkEffect
 * Signature: void PostLoad(ChunkEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ChunkEffect::PostLoad(ChunkEffect *this)

{
  SmokeEmitter *pSVar1;
  
  pSVar1 = SmokeEffect::AddEmitter
                     (&smokeEffect,this->smokeTexture,this->smokeFrames,
                      (float)this->smokeFrames / this->smokeLifespan,this->smokeRadius,1.0);
  this->smokeEmitter = pSVar1;
  return;
}
