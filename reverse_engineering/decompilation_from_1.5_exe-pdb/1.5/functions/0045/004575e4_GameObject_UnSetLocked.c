/*
 * Entry: 004575e4
 * Name: GameObject::UnSetLocked
 * Namespace: GameObject
 * Signature: void UnSetLocked(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::UnSetLocked(GameObject *this,int param_1)

{
  this->locked = this->locked & ~(1 << ((byte)param_1 & 0x1f));
  return;
}
