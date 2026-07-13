/*
 * Entry: 004575d0
 * Name: GameObject::SetLocked
 * Namespace: GameObject
 * Signature: void SetLocked(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetLocked(GameObject *this,int param_1)

{
  this->locked = this->locked | 1 << ((byte)param_1 & 0x1f);
  return;
}
