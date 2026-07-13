/*
 * Entry: 00542ff0
 * Name: D3D_Flip
 * Namespace: Global
 * Signature: int D3D_Flip(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Flip(VIDEO_DEVICE *param_1)

{
  int iVar1;
  
  if (0 < hWinRef) {
    hWinRef = 1;
    D3D_Release_DC(param_1);
  }
  if (D3D_Device_Lost != 0) {
    iVar1 = D3DAppIResetDevice();
    return iVar1;
  }
  iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->Present)
                    (d3dappi.lpD3DDevice,(tagRECT *)0x0,(tagRECT *)0x0,(HWND__ *)0x0,(_RGNDATA *)0x0
                    );
  if (iVar1 == -0x7789f798) {
    Trace("Present: D3D device lost\n");
    D3D_Device_Lost = 1;
  }
  else if ((ResolutionMode != 0) && (((byte)D3IniFlags & 1) != 0)) {
    iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->Clear)(d3dappi.lpD3DDevice,0,(_D3DRECT *)0x0,2,0,1.0,0)
    ;
  }
  return (uint)(iVar1 == 0);
}
