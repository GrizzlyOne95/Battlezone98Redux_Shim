/*
 * Entry: 0059a5a4
 * Name: _SetDIBitsToDevice@48
 * Namespace: Global
 * Signature: int _SetDIBitsToDevice@48(HDC hdc, int xDest, int yDest, DWORD w, DWORD h, int xSrc, int ySrc, UINT StartScan, UINT cLines, void * lpvBits, BITMAPINFO * lpbmi, UINT ColorUse)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _SetDIBitsToDevice_48
              (HDC hdc,int xDest,int yDest,DWORD w,DWORD h,int xSrc,int ySrc,UINT StartScan,
              UINT cLines,void *lpvBits,BITMAPINFO *lpbmi,UINT ColorUse)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SetDIBitsToDevice(hdc,xDest,yDest,w,h,xSrc,ySrc,StartScan,cLines,lpvBits,lpbmi,ColorUse);
  return iVar1;
}
