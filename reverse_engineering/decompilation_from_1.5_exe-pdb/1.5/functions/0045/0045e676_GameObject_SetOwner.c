/*
 * Entry: 0045e676
 * Name: GameObject::SetOwner
 * Namespace: GameObject
 * Signature: void SetOwner(GameObject * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetOwner(GameObject *this,GameObject *param_1)

{
  int iVar1;
  
  if (param_1 == (GameObject *)0x0) {
    this->ownerHandle = 0;
  }
  else {
    iVar1 = GetHandle(param_1);
    this->ownerHandle = iVar1;
  }
  return;
}
