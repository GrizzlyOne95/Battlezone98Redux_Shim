/*
 * Entry: 004b09f1
 * Name: RtimeClass::CreateObject
 * Namespace: RtimeClass
 * Signature: SObject * CreateObject(RtimeClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __thiscall RtimeClass::CreateObject(RtimeClass *this)

{
  SObject *pSVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b09f1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pSVar1 = (*this->m_pfnCreateObject)();
  return pSVar1;
}
