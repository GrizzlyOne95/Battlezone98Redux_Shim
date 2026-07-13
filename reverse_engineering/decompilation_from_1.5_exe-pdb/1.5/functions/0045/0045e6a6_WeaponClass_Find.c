/*
 * Entry: 0045e6a6
 * Name: WeaponClass::Find
 * Namespace: WeaponClass
 * Signature: WeaponClass * Find(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __cdecl WeaponClass::Find(char *param_1)

{
  WeaponClass *pWVar1;
  long64 lVar2;
  
  lVar2 = StringToPrjID(param_1);
  pWVar1 = Find(lVar2);
  return pWVar1;
}
