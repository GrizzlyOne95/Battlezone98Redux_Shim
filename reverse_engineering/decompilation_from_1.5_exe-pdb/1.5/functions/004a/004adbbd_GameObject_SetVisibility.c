/*
 * Entry: 004adbbd
 * Name: GameObject::SetVisibility
 * Namespace: GameObject
 * Signature: void SetVisibility(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetVisibility(GameObject *this,int param_1)

{
  uint uVar1;
  
  uVar1 = 1 << ((byte)param_1 & 0x1f);
  this->isVisible = this->isVisible | uVar1;
  this->seen = this->seen | uVar1;
  return;
}
