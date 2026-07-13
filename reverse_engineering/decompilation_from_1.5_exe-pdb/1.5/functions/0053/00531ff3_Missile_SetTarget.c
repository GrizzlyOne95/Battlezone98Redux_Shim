/*
 * Entry: 00531ff3
 * Name: Missile::SetTarget
 * Namespace: Missile
 * Signature: void SetTarget(Missile * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Missile::SetTarget(Missile *this,GameObject *param_1)

{
  int iVar1;
  
  if (param_1 == (GameObject *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = GameObject::GetHandle(param_1);
  }
  this->targetHandle = iVar1;
  return;
}
