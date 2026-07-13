/*
 * Entry: 00410b36
 * Name: RigEnemy::CreateObject
 * Namespace: RigEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RigEnemy::CreateObject(void)

{
  RigEnemy *pRVar1;
  
  pRVar1 = operator_new(0x58);
  if (pRVar1 != (RigEnemy *)0x0) {
    pRVar1 = RigEnemy(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
