/*
 * Entry: 004570ec
 * Name: PatrolTask_Build
 * Namespace: Global
 * Signature: AiTask * PatrolTask_Build(Craft * param_1, AiPath * param_2, goal_type_enum param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask * __cdecl PatrolTask_Build(Craft *param_1,AiPath *param_2,goal_type_enum param_3)

{
  PatrolTask *pPVar1;
  
  pPVar1 = operator_new(0x15c);
  if (pPVar1 != (PatrolTask *)0x0) {
    pPVar1 = PatrolTask::PatrolTask(pPVar1,param_1,param_2,param_3);
    return (AiTask *)pPVar1;
  }
  return (AiTask *)0x0;
}
