/*
 * Entry: 0045e553
 * Name: GameObject::GetMaxAmmo
 * Namespace: GameObject
 * Signature: long GetMaxAmmo(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __thiscall GameObject::GetMaxAmmo(GameObject *this)

{
  return this->maxAmmo ^ 0x33333333;
}
