/*
 * Entry: 0040e161
 * Name: std::_Construct<AttackerInfo,AttackerInfo>
 * Namespace: std
 * Signature: void _Construct<AttackerInfo,AttackerInfo>(AttackerInfo * param_1, AttackerInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AttackerInfo,AttackerInfo>(AttackerInfo *param_1,AttackerInfo *param_2)

{
  if (param_1 != (AttackerInfo *)0x0) {
    param_1->attacker = param_2->attacker;
    param_1->attackTask = param_2->attackTask;
  }
  return;
}
