/*
 * Entry: 0045e699
 * Name: GameObject::GetOwner
 * Namespace: GameObject
 * Signature: GameObject * GetOwner(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall GameObject::GetOwner(GameObject *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GetObj(this->ownerHandle);
  return pGVar1;
}
