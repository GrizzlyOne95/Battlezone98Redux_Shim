/*
 * Entry: 004670a4
 * Name: FastLeft
 * Namespace: Global
 * Signature: void FastLeft(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FastLeft(ActionInfo *param_1)

{
  ctrl_braccel(param_1->me,1000.0);
  ctrl_steer(param_1->me,param_1->my_head - 0.7853982);
  return;
}
