/*
 * Entry: 004707d0
 * Name: ScoutEnemy::CreateObject
 * Namespace: ScoutEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl ScoutEnemy::CreateObject(void)

{
  ScoutEnemy *pSVar1;
  
  pSVar1 = operator_new(0x78);
  if (pSVar1 != (ScoutEnemy *)0x0) {
    pSVar1 = ScoutEnemy(pSVar1);
    return (SObject *)pSVar1;
  }
  return (SObject *)0x0;
}
