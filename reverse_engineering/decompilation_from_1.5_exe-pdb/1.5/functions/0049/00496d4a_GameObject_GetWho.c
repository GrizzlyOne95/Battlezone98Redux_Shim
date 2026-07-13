/*
 * Entry: 00496d4a
 * Name: GameObject::GetWho
 * Namespace: GameObject
 * Signature: GameObject * GetWho(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall GameObject::GetWho(GameObject *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj((this->curCmd).who);
  return pGVar1;
}
