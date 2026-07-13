/*
 * Entry: 0059a544
 * Name: _LoadImageA@24
 * Namespace: Global
 * Signature: HANDLE _LoadImageA@24(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _LoadImageA_24(HINSTANCE hInst,LPCSTR name,UINT type,int cx,int cy,UINT fuLoad)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a544. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LoadImageA(hInst,name,type,cx,cy,fuLoad);
  return pvVar1;
}
