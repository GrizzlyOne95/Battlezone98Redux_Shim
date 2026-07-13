/*
 * Entry: 004599c5
 * Name: RecyclerEnemy::CreateObject
 * Namespace: RecyclerEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RecyclerEnemy::CreateObject(void)

{
  RecyclerEnemy *pRVar1;
  
  pRVar1 = operator_new(0x58);
  if (pRVar1 != (RecyclerEnemy *)0x0) {
    pRVar1 = RecyclerEnemy(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
