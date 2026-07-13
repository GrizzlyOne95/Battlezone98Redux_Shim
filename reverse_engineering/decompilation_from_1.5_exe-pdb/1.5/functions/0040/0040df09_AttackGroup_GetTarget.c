/*
 * Entry: 0040df09
 * Name: AttackGroup::GetTarget
 * Namespace: AttackGroup
 * Signature: GameObject * GetTarget(AttackGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall AttackGroup::GetTarget(AttackGroup *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(this->target);
  return pGVar1;
}
