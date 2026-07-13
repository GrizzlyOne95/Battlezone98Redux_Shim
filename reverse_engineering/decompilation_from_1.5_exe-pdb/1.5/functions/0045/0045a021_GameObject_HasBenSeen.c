/*
 * Entry: 0045a021
 * Name: GameObject::HasBenSeen
 * Namespace: GameObject
 * Signature: bool HasBenSeen(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::HasBenSeen(GameObject *this,int param_1)

{
  return (bool)((byte)(this->seen >> ((byte)param_1 & 0x1f)) & 1);
}
