/*
 * Entry: 0040bfa4
 * Name: APCEnemy::CreateObject
 * Namespace: APCEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl APCEnemy::CreateObject(void)

{
  APCEnemy *pAVar1;
  
  pAVar1 = operator_new(0x58);
  if (pAVar1 != (APCEnemy *)0x0) {
    pAVar1 = APCEnemy(pAVar1);
    return (SObject *)pAVar1;
  }
  return (SObject *)0x0;
}
