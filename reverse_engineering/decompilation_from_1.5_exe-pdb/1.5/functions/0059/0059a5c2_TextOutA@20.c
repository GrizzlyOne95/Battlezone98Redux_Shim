/*
 * Entry: 0059a5c2
 * Name: _TextOutA@20
 * Namespace: Global
 * Signature: BOOL _TextOutA@20(HDC hdc, int x, int y, LPCSTR lpString, int c)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _TextOutA_20(HDC hdc,int x,int y,LPCSTR lpString,int c)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5c2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TextOutA(hdc,x,y,lpString,c);
  return BVar1;
}
