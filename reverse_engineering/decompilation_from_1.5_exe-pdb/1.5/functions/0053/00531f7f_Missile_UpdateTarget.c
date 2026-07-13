/*
 * Entry: 00531f7f
 * Name: Missile::UpdateTarget
 * Namespace: Missile
 * Signature: GameObject * UpdateTarget(Missile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Missile::UpdateTarget(Missile *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(this->targetHandle);
  if (pGVar1 == (GameObject *)0x0) {
    this->targetHandle = 0;
  }
  return pGVar1;
}
