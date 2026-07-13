/*
 * Entry: 0040e178
 * Name: std::_Construct<AttackGroup_*,AttackGroup_*>
 * Namespace: std
 * Signature: void _Construct<AttackGroup_*,AttackGroup_*>(AttackGroup * * param_1, AttackGroup * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Construct<AttackGroup_*,AttackGroup_*>(AttackGroup **param_1,AttackGroup **param_2)

{
  if (param_1 != (AttackGroup **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
