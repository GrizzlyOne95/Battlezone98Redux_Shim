/*
 * Entry: 004d886a
 * Name: Reticle::PreLoad
 * Namespace: Reticle
 * Signature: void PreLoad(Reticle * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Reticle::PreLoad(Reticle *this)

{
  int iVar1;
  
  iVar1 = GetSpriteIndex("dot");
  this->defaultIndex = iVar1;
  iVar1 = GetSpriteIndex("ground.G");
  this->groundIndex = iVar1;
  iVar1 = GetSpriteIndex("dot");
  this->dotIndex = iVar1;
  iVar1 = GetSpriteIndex("sight");
  this->horizonIndex = iVar1;
  return;
}
