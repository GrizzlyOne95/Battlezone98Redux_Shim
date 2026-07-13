/*
 * Entry: 0059a496
 * Name: _CreateWindowExA@48
 * Namespace: Global
 * Signature: HWND _CreateWindowExA@48(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _CreateWindowExA_48(DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,int X,
                        int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance
                        ,LPVOID lpParam)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a496. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateWindowExA(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,
                           hMenu,hInstance,lpParam);
  return pHVar1;
}
