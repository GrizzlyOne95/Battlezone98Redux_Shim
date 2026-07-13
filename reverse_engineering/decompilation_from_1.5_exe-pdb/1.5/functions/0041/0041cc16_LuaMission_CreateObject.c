/*
 * Entry: 0041cc16
 * Name: LuaMission::CreateObject
 * Namespace: LuaMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl LuaMission::CreateObject(void)

{
  LuaMission *pLVar1;
  
  pLVar1 = operator_new(0x48);
  if (pLVar1 != (LuaMission *)0x0) {
    pLVar1 = LuaMission(pLVar1);
    return (SObject *)pLVar1;
  }
  return (SObject *)0x0;
}
