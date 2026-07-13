/*
 * Entry: 00496d57
 * Name: GameObject::AddAmmo
 * Namespace: GameObject
 * Signature: void AddAmmo(GameObject * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::AddAmmo(GameObject *this,long param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (0 < (int)(this->maxAmmo ^ 0x33333333U)) {
    if (((this == userObject) && (param_1 < 1)) && (iVar1 = UserPref_unlimitedAmmo(), iVar1 != 0)) {
      return;
    }
    uVar2 = (this->curAmmo ^ 0x33333333U) + param_1;
    uVar3 = this->maxAmmo ^ 0x33333333;
    if ((int)uVar3 <= (int)uVar2) {
      uVar2 = uVar3;
    }
    SetCurAmmo(this,uVar2);
  }
  return;
}
