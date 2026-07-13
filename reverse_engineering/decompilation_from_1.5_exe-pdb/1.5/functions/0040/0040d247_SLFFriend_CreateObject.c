/*
 * Entry: 0040d247
 * Name: SLFFriend::CreateObject
 * Namespace: SLFFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SLFFriend::CreateObject(void)

{
  SLFFriend *pSVar1;
  
  pSVar1 = operator_new(0x48);
  if (pSVar1 != (SLFFriend *)0x0) {
    pSVar1 = SLFFriend(pSVar1);
    return (SObject *)pSVar1;
  }
  return (SObject *)0x0;
}
