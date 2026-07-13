/*
 * Entry: 0053fe3f
 * Name: D3DAppCreateFromHWND
 * Namespace: Global
 * Signature: int D3DAppCreateFromHWND(int param_1, int param_2, HWND__ * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppCreateFromHWND(int param_1,int param_2,HWND__ *param_3)

{
  int iVar1;
  int iVar2;
  
  d3dappi.bIsSim = param_1;
  d3dappi.bWindowed = param_2;
  d3dappi.hwnd = param_3;
  iVar1 = D3DAppICreateD3D();
  if ((iVar1 != 0) && (iVar2 = D3DAppISelectDisplayMode(), iVar1 = d3dappi.CurrMode, iVar2 != 0)) {
    D3DAppIGetClientWin(param_3);
    if (d3dappi.bWindowed == 0) {
      szLastClient.cx = d3dappi.szClient.cx;
      szLastClient.cy = d3dappi.szClient.cy;
      d3dappi.szClient.cx = d3dappi.Mode[iVar1].Width;
      d3dappi.szClient.cy = d3dappi.Mode[iVar1].Height;
      d3dappi.SavedWindowRect.left = d3dappi.WindowsDisplay.Width - d3dappi.szClient.cx >> 1;
      d3dappi.SavedWindowRect.right = d3dappi.SavedWindowRect.left + d3dappi.szClient.cx;
      d3dappi.SavedWindowRect.top = 0;
      d3dappi.SavedWindowRect.bottom = d3dappi.szClient.cy;
    }
    else {
      GetWindowRect((HWND)param_3,(LPRECT)&d3dappi.SavedWindowRect);
    }
    if ((d3dappi.bIsSim == 0) ||
       ((iVar1 = D3DAppICreateDevice(), iVar1 != 0 &&
        (iVar1 = InitTLExecuteBuffer(d3dappi.lpD3DDevice), iVar1 != 0)))) {
      return 1;
    }
  }
  ReleaseTLExecuteBuffer();
  if (d3dappi.lpBackBuffer != (IDirect3DSurface9 *)0x0) {
    (*(d3dappi.lpBackBuffer)->lpVtbl->Release)(d3dappi.lpBackBuffer);
    d3dappi.lpBackBuffer = (IDirect3DSurface9 *)0x0;
  }
  if (d3dappi.lpD3DDevice != (IDirect3DDevice9 *)0x0) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->Release)(d3dappi.lpD3DDevice);
    d3dappi.lpD3DDevice = (IDirect3DDevice9 *)0x0;
  }
  if (d3dappi.lpD3D != (IDirect3D9 *)0x0) {
    (*(d3dappi.lpD3D)->lpVtbl->Release)(d3dappi.lpD3D);
    d3dappi.lpD3D = (IDirect3D9 *)0x0;
  }
  return 0;
}
