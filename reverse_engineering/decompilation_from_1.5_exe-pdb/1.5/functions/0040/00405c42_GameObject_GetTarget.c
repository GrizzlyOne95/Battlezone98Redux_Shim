/*
 * Entry: 00405c42
 * Name: GameObject::GetTarget
 * Namespace: GameObject
 * Signature: GameObject * GetTarget(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall GameObject::GetTarget(GameObject *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GetObj(this->targetHandle);
  return pGVar1;
}
