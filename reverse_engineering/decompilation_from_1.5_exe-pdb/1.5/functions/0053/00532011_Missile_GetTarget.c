/*
 * Entry: 00532011
 * Name: Missile::GetTarget
 * Namespace: Missile
 * Signature: GameObject * GetTarget(Missile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Missile::GetTarget(Missile *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(this->targetHandle);
  return pGVar1;
}
