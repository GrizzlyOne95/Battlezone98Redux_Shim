/*
 * Entry: 00414a95
 * Name: GotoTask::CreateObject
 * Namespace: GotoTask
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl GotoTask::CreateObject(void)

{
  GotoTask *pGVar1;
  
  pGVar1 = operator_new(0x150);
  if (pGVar1 != (GotoTask *)0x0) {
    pGVar1 = GotoTask(pGVar1);
    return (SObject *)pGVar1;
  }
  return (SObject *)0x0;
}
