/*
 * Entry: 00540039
 * Name: D3DAppICreateDevice
 * Namespace: Global
 * Signature: int D3DAppICreateDevice(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppICreateDevice(void)

{
  _D3DPRESENT_PARAMETERS_ *p_Var1;
  _D3DPRESENT_PARAMETERS_ local_40;
  ulong local_8;
  
  if (d3dappi.lpBackBuffer != (IDirect3DSurface9 *)0x0) {
    (*(d3dappi.lpBackBuffer)->lpVtbl->Release)(d3dappi.lpBackBuffer);
    d3dappi.lpBackBuffer = (IDirect3DSurface9 *)0x0;
  }
  if (d3dappi.lpD3DDevice != (IDirect3DDevice9 *)0x0) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->Release)(d3dappi.lpD3DDevice);
    d3dappi.lpD3DDevice = (IDirect3DDevice9 *)0x0;
  }
  LastError = (*(d3dappi.lpD3D)->lpVtbl->GetDeviceCaps)
                        (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,&d3dappi.Caps);
  if (-1 < LastError) {
    p_Var1 = (_D3DPRESENT_PARAMETERS_ *)d3dappi.lpD3D;
    LastError = (*(d3dappi.lpD3D)->lpVtbl->CheckDeviceMultiSampleType)
                          (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,d3dappi.PixelFormat,d3dappi.bWindowed,
                           d3dappi.MultiSampleType,&local_8);
    if (LastError < 0) {
      D3DAppISetErrorString
                ("The device does not support multisample type %d.\nResetting to none.\n");
      MessageBoxA((HWND)0x0,LastErrorString,"D3D Device Warning",0);
      LastErrorString[0] = '\0';
      d3dappi.MultiSampleType = D3DMULTISAMPLE_NONE;
      d3dappi.MultiSampleQuality = 0;
    }
    if (d3dappi.MultiSampleQuality < 0) {
      d3dappi.MultiSampleQuality = 0;
    }
    if ((int)local_8 <= d3dappi.MultiSampleQuality) {
      D3DAppISetErrorString
                (
                "Multisample type %d does not support quality level %d.\nResetting to the maximum value of %d.\n"
                );
      MessageBoxA((HWND)0x0,LastErrorString,"D3D Device Warning",0);
      d3dappi.MultiSampleQuality = local_8 - 1;
      LastErrorString[0] = '\0';
    }
    D3DAppISetupPresentParameters(p_Var1);
    if ((((d3dappi.Caps.DevCaps & 0x10000) != 0) &&
        (LastError = (*(d3dappi.lpD3D)->lpVtbl->CreateDevice)
                               (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,d3dappi.hwnd,0x42,&local_40,
                                &d3dappi.lpD3DDevice), -1 < LastError)) ||
       (LastError = (*(d3dappi.lpD3D)->lpVtbl->CreateDevice)
                              (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,d3dappi.hwnd,0x22,&local_40,
                               &d3dappi.lpD3DDevice), -1 < LastError)) {
      (*(d3dappi.lpD3DDevice)->lpVtbl->GetBackBuffer)
                (d3dappi.lpD3DDevice,0,0,D3DBACKBUFFER_TYPE_MONO,&d3dappi.lpBackBuffer);
      return 1;
    }
    D3DAppErrorToString(LastError);
    D3DAppISetErrorString("Create D3D device failed.\n%s");
  }
  if (d3dappi.lpD3DDevice != (IDirect3DDevice9 *)0x0) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->Release)(d3dappi.lpD3DDevice);
    d3dappi.lpD3DDevice = (IDirect3DDevice9 *)0x0;
  }
  return 0;
}
