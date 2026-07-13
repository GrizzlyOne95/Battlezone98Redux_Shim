/*
 * Entry: 00467166
 * Name: FastStraight
 * Namespace: Global
 * Signature: void FastStraight(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FastStraight(ActionInfo *param_1)

{
  ctrl_braccel(param_1->me,1000.0);
  ctrl_steer(param_1->me,param_1->my_head);
  return;
}
