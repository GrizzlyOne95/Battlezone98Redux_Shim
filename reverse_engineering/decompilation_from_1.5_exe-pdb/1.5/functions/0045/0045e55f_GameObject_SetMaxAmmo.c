/*
 * Entry: 0045e55f
 * Name: GameObject::SetMaxAmmo
 * Namespace: GameObject
 * Signature: void SetMaxAmmo(GameObject * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetMaxAmmo(GameObject *this,long param_1)

{
  this->maxAmmo = param_1 ^ 0x33333333;
  if (0 < param_1) {
    this->ammoRatio = (float)(int)(this->curAmmo ^ 0x33333333) / (float)param_1;
  }
  return;
}
