/*
 * Entry: 00460a8c
 * Name: GameObject::SetCurAmmo
 * Namespace: GameObject
 * Signature: void SetCurAmmo(GameObject * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetCurAmmo(GameObject *this,long param_1)

{
  uint uVar1;
  
  uVar1 = this->maxAmmo ^ 0x33333333;
  this->curAmmo = param_1 ^ 0x33333333;
  if (0 < (int)uVar1) {
    this->ammoRatio = (float)param_1 / (float)(int)uVar1;
  }
  return;
}
