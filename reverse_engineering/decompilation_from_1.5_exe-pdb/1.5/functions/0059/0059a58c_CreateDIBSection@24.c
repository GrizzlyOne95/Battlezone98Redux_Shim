/*
 * Entry: 0059a58c
 * Name: _CreateDIBSection@24
 * Namespace: Global
 * Signature: HBITMAP _CreateDIBSection@24(HDC hdc, BITMAPINFO * lpbmi, UINT usage, void * * ppvBits, HANDLE hSection, DWORD offset)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HBITMAP _CreateDIBSection_24
                  (HDC hdc,BITMAPINFO *lpbmi,UINT usage,void **ppvBits,HANDLE hSection,DWORD offset)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a58c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateDIBSection(hdc,lpbmi,usage,ppvBits,hSection,offset);
  return pHVar1;
}
