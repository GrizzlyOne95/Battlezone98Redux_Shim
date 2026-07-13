/*
 * Entry: 0045af9a
 * Name: RecycleTask_Build
 * Namespace: Global
 * Signature: AiTask * RecycleTask_Build(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask * __cdecl RecycleTask_Build(GameObject *param_1,GameObject *param_2)

{
  RecycleTask *pRVar1;
  
  pRVar1 = operator_new(0x70);
  if (pRVar1 != (RecycleTask *)0x0) {
    pRVar1 = RecycleTask::RecycleTask(pRVar1,(Craft *)param_1,param_2);
    return (AiTask *)pRVar1;
  }
  return (AiTask *)0x0;
}
