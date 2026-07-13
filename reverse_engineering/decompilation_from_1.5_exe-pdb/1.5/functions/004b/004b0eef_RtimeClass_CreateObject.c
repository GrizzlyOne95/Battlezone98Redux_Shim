/*
 * Entry: 004b0eef
 * Name: RtimeClass::CreateObject
 * Namespace: RtimeClass
 * Signature: SObject * CreateObject(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RtimeClass::CreateObject(char *param_1)

{
  RtimeClass *pRVar1;
  SObject *pSVar2;
  
  pRVar1 = GetRtimeClass(param_1);
                    /* WARNING: Could not recover jumptable at 0x004b0ef9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pSVar2 = (*pRVar1->m_pfnCreateObject)();
  return pSVar2;
}
