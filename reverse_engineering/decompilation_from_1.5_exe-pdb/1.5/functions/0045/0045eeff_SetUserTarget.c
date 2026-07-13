/*
 * Entry: 0045eeff
 * Name: SetUserTarget
 * Namespace: Global
 * Signature: void SetUserTarget(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetUserTarget(int param_1)

{
  GameObject *this;
  GameObject *pGVar1;
  
  this = GameObject::userObject;
  if (GameObject::userObject != (GameObject *)0x0) {
    pGVar1 = GameObjectHandle::GetObj(param_1);
    GameObject::SetTarget(this,pGVar1);
  }
  return;
}
