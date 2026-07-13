/*
 * Entry: 00467109
 * Name: FastRight
 * Namespace: Global
 * Signature: void FastRight(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FastRight(ActionInfo *param_1)

{
  ctrl_braccel(param_1->me,1000.0);
  ctrl_steer(param_1->me,param_1->my_head + 0.7853982);
  return;
}
