/*
 * Entry: 0041118f
 * Name: DemoMission::CreateObject
 * Namespace: DemoMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl DemoMission::CreateObject(void)

{
  DemoMission *pDVar1;
  
  pDVar1 = operator_new(0xe8);
  if (pDVar1 != (DemoMission *)0x0) {
    pDVar1 = DemoMission(pDVar1);
    return (SObject *)pDVar1;
  }
  return (SObject *)0x0;
}
