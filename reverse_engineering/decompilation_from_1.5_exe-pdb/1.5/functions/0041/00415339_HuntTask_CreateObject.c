/*
 * Entry: 00415339
 * Name: HuntTask::CreateObject
 * Namespace: HuntTask
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl HuntTask::CreateObject(void)

{
  HuntTask *pHVar1;
  
  pHVar1 = operator_new(0x16c);
  if (pHVar1 != (HuntTask *)0x0) {
    pHVar1 = HuntTask(pHVar1);
    return (SObject *)pHVar1;
  }
  return (SObject *)0x0;
}
