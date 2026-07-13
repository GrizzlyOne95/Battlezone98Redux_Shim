/*
 * Entry: 004585b7
 * Name: PowerUpProcess::CreateObject
 * Namespace: PowerUpProcess
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl PowerUpProcess::CreateObject(void)

{
  PowerUpProcess *pPVar1;
  
  pPVar1 = operator_new(0x14);
  if (pPVar1 != (PowerUpProcess *)0x0) {
    pPVar1 = PowerUpProcess(pPVar1);
    return (SObject *)pPVar1;
  }
  return (SObject *)0x0;
}
