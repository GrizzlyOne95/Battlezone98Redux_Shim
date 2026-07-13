/*
 * Entry: 0059a628
 * Name: _GetObjectA@12
 * Namespace: Global
 * Signature: int _GetObjectA@12(HANDLE h, int c, LPVOID pv)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _GetObjectA_12(HANDLE h,int c,LPVOID pv)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetObjectA(h,c,pv);
  return iVar1;
}
