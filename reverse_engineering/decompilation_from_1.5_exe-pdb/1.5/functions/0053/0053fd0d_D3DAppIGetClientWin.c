/*
 * Entry: 0053fd0d
 * Name: D3DAppIGetClientWin
 * Namespace: Global
 * Signature: void D3DAppIGetClientWin(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3DAppIGetClientWin(HWND__ *param_1)

{
  tagRECT local_14;
  
  d3dappi.pClientOnPrimary.y = 0;
  d3dappi.pClientOnPrimary.x = 0;
  if (d3dappi.bWindowed == 0) {
    d3dappi.szClient.cx = d3dappi.ThisMode.Width;
    local_14.bottom = d3dappi.ThisMode.Height;
  }
  else {
    ClientToScreen((HWND)param_1,(LPPOINT)&d3dappi.pClientOnPrimary);
    GetClientRect((HWND)param_1,&local_14);
    d3dappi.szClient.cx = local_14.right;
  }
  d3dappi.szClient.cy = local_14.bottom;
  return;
}
