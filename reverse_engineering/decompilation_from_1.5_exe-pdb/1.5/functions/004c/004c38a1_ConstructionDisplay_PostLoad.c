/*
 * Entry: 004c38a1
 * Name: ConstructionDisplay::PostLoad
 * Namespace: ConstructionDisplay
 * Signature: void PostLoad(ConstructionDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionDisplay::PostLoad(ConstructionDisplay *this)

{
  int iVar1;
  
  this->index = 0;
  iVar1 = GetSpriteIndex("ground.G");
  this->rectGreen = iVar1;
  iVar1 = GetSpriteIndex("ground.Y");
  this->rectYellow = iVar1;
  iVar1 = GetSpriteIndex("ground.R");
  this->rectRed = iVar1;
  return;
}
