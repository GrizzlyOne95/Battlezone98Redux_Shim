/*
 * Entry: 0040df13
 * Name: AttackGroup::GetAttackCount
 * Namespace: AttackGroup
 * Signature: int GetAttackCount(AttackGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AttackGroup::GetAttackCount(AttackGroup *this)

{
  return (this->attackers)._Mysize;
}
