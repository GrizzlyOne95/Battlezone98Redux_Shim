/*
 * Entry: 004105ec
 * Name: UnBuild::CreateObject
 * Namespace: UnBuild
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl UnBuild::CreateObject(void)

{
  UnBuild *pUVar1;
  
  pUVar1 = operator_new(0x164);
  if (pUVar1 != (UnBuild *)0x0) {
    pUVar1 = UnBuild(pUVar1);
    return (SObject *)pUVar1;
  }
  return (SObject *)0x0;
}
