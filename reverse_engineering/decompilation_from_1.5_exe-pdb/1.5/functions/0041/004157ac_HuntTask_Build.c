/*
 * Entry: 004157ac
 * Name: HuntTask_Build
 * Namespace: Global
 * Signature: AiTask * HuntTask_Build(Craft * param_1, AiPath * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask * __cdecl HuntTask_Build(Craft *param_1,AiPath *param_2)

{
  HuntTask *pHVar1;
  
  pHVar1 = operator_new(0x16c);
  if (pHVar1 != (HuntTask *)0x0) {
    pHVar1 = HuntTask::HuntTask(pHVar1,param_1,param_2);
    return (AiTask *)pHVar1;
  }
  return (AiTask *)0x0;
}
