/*
 * Entry: 0059a61c
 * Name: _CreateBitmap@20
 * Namespace: Global
 * Signature: HBITMAP _CreateBitmap@20(int nWidth, int nHeight, UINT nPlanes, UINT nBitCount, void * lpBits)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HBITMAP _CreateBitmap_20(int nWidth,int nHeight,UINT nPlanes,UINT nBitCount,void *lpBits)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a61c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateBitmap(nWidth,nHeight,nPlanes,nBitCount,lpBits);
  return pHVar1;
}
