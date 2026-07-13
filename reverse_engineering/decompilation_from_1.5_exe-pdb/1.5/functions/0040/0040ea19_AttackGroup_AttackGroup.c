/*
 * Entry: 0040ea19
 * Name: AttackGroup::AttackGroup
 * Namespace: AttackGroup
 * Signature: AttackGroup * AttackGroup(AttackGroup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AttackGroup * __thiscall AttackGroup::AttackGroup(AttackGroup *this)

{
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::
  list<AttackerInfo,std::allocator<AttackerInfo>_>(&this->attackers);
  return this;
}
