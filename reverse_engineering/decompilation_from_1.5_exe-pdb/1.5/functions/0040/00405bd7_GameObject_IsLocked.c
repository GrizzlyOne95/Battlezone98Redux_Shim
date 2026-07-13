/*
 * Entry: 00405bd7
 * Name: GameObject::IsLocked
 * Namespace: GameObject
 * Signature: bool IsLocked(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::IsLocked(GameObject *this,int param_1)

{
  return (bool)((byte)(this->locked >> ((byte)param_1 & 0x1f)) & 1);
}
