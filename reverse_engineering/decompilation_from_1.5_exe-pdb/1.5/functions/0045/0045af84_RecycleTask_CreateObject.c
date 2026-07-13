/*
 * Entry: 0045af84
 * Name: RecycleTask::CreateObject
 * Namespace: RecycleTask
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RecycleTask::CreateObject(void)

{
  RecycleTask *pRVar1;
  
  pRVar1 = operator_new(0x70);
  if (pRVar1 != (RecycleTask *)0x0) {
    pRVar1 = RecycleTask(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
