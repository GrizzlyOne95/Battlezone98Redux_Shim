/*
 * Entry: 0045a075
 * Name: Scavenger::UnloadScrap
 * Namespace: Scavenger
 * Signature: void UnloadScrap(Scavenger * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scavenger::UnloadScrap(Scavenger *this,int param_1)

{
  int iVar1;
  
  iVar1 = Clamp(this->scrapHeld - param_1,0,this->maxScrap);
  this->scrapHeld = iVar1;
  return;
}
