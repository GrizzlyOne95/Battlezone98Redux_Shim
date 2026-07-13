/*
 * Entry: 0046713b
 * Name: SlowStraight
 * Namespace: Global
 * Signature: void SlowStraight(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SlowStraight(ActionInfo *param_1)

{
  float fVar1;
  
  fVar1 = get_max_turning_v(param_1->me);
  ctrl_braccel(param_1->me,fVar1);
  ctrl_steer(param_1->me,param_1->my_head);
  return;
}
