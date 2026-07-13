/*
 * Entry: 0059a598
 * Name: _SetMapperFlags@8
 * Namespace: Global
 * Signature: DWORD _SetMapperFlags@8(HDC hdc, DWORD flags)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _SetMapperFlags_8(HDC hdc,DWORD flags)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a598. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = SetMapperFlags(hdc,flags);
  return DVar1;
}
