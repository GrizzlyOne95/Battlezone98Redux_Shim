/*
 * Entry: 0045ef8e
 * Name: SetOwner
 * Namespace: Global
 * Signature: void SetOwner(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetOwner(int param_1,int param_2)

{
  GameObject *this;
  GameObject *pGVar1;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    pGVar1 = GameObjectHandle::GetObj(param_2);
    GameObject::SetOwner(this,pGVar1);
  }
  return;
}
