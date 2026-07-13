/*
 * Entry: 00405bc5
 * Name: GameObject::IsVisibleTo
 * Namespace: GameObject
 * Signature: bool IsVisibleTo(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::IsVisibleTo(GameObject *this,int param_1)

{
  return (bool)((byte)(this->isVisible >> ((byte)param_1 & 0x1f)) & 1);
}
