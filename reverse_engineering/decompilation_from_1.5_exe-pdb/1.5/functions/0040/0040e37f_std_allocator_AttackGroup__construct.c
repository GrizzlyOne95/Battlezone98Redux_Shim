/*
 * Entry: 0040e37f
 * Name: std::allocator<AttackGroup_*>::construct
 * Namespace: std::allocator<AttackGroup_*>
 * Signature: void construct(allocator<AttackGroup_*> * this, AttackGroup * * param_1, AttackGroup * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AttackGroup_*>::construct
          (allocator<AttackGroup_*> *this,AttackGroup **param_1,AttackGroup **param_2)

{
  if (param_1 != (AttackGroup **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
