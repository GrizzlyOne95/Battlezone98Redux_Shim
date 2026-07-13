/*
 * Entry: 004d9e73
 * Name: ShockWaveEffect::PreLoad
 * Namespace: ShockWaveEffect
 * Signature: void PreLoad(ShockWaveEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShockWaveEffect::PreLoad(ShockWaveEffect *this)

{
  int iVar1;
  
  iVar1 = GetSpriteIndex("shockwave.0");
  this->shockwaveIndex = iVar1;
  this->shockwaveFrames = iVar1 + 0x10;
  return;
}
