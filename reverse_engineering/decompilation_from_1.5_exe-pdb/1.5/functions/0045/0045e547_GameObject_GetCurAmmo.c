/*
 * Entry: 0045e547
 * Name: GameObject::GetCurAmmo
 * Namespace: GameObject
 * Signature: long GetCurAmmo(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __thiscall GameObject::GetCurAmmo(GameObject *this)

{
  return this->curAmmo ^ 0x33333333;
}
