/*
 * Entry: 0045a033
 * Name: GameObject::SetTarget
 * Namespace: GameObject
 * Signature: void SetTarget(GameObject * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetTarget(GameObject *this,GameObject *param_1)

{
  int iVar1;
  
  if (param_1 == (GameObject *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = GetHandle(param_1);
  }
  this->targetHandle = iVar1;
  return;
}
