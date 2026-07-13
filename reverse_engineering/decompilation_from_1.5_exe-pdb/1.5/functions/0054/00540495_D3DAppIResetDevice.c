/*
 * Entry: 00540495
 * Name: D3DAppIResetDevice
 * Namespace: Global
 * Signature: int D3DAppIResetDevice(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppIResetDevice(void)

{
  int iVar1;
  code *_StartAddress;
  int unaff_ESI;
  HANDLE unaff_EDI;
  char *in_stack_ffffff8c;
  tagD3DAppInfo *ptVar2;
  _D3DPRESENT_PARAMETERS_ *hEvent;
  HANDLE local_4c;
  uintptr_t local_48;
  _D3DPRESENT_PARAMETERS_ local_44;
  
  local_48 = 0;
  local_4c = (HANDLE)0x0;
  local_44.BackBufferWidth = 1;
  iVar1 = Net_IsNetGame();
  if (iVar1 != 0) {
    local_4c = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,"WaitForReset");
    _StartAddress = ThreadNetEscape;
    if (MainLoopRunning == 0) {
      _StartAddress = ThreadSyncTimer;
    }
    in_stack_ffffff8c = (char *)0x0;
    local_48 = _beginthreadex((void *)0x0,0,_StartAddress,&local_4c,0,&local_44.BackBufferFormat);
  }
  local_44.BackBufferHeight = timeGetTime();
  hEvent = (_D3DPRESENT_PARAMETERS_ *)0x540504;
  ReleaseTLExecuteBuffer();
  if (d3dappi.lpBackBuffer != (IDirect3DSurface9 *)0x0) {
    hEvent = (_D3DPRESENT_PARAMETERS_ *)d3dappi.lpBackBuffer;
    (*(d3dappi.lpBackBuffer)->lpVtbl->Release)(d3dappi.lpBackBuffer);
    d3dappi.lpBackBuffer = (IDirect3DSurface9 *)0x0;
  }
  D3DAppISetupPresentParameters(hEvent);
  do {
    iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->TestCooperativeLevel)(d3dappi.lpD3DDevice);
    if (iVar1 == -0x7789f798) {
LAB_00540544:
      Trace(in_stack_ffffff8c);
      D3D_Device_Lost = 1;
      HandleMessageQueue(&Device);
      in_stack_ffffff8c = (char *)0x64;
      Sleep(100);
    }
    else {
      if ((iVar1 != 0) && (iVar1 != -0x7789f797)) {
        Trace("Reset: unexpected error %08x\n");
LAB_00540687:
        unaff_ESI = 0;
        goto LAB_0054063d;
      }
      if (d3dappi.lpBackBuffer != (IDirect3DSurface9 *)0x0) {
        (*(d3dappi.lpBackBuffer)->lpVtbl->Release)(d3dappi.lpBackBuffer);
        d3dappi.lpBackBuffer = (IDirect3DSurface9 *)0x0;
      }
      ptVar2 = (tagD3DAppInfo *)d3dappi.lpD3DDevice;
      iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->Reset)(d3dappi.lpD3DDevice,&local_44);
      if (iVar1 == -0x7789f798) {
        in_stack_ffffff8c = "Reset: device reset returned device lost\n";
        goto LAB_00540544;
      }
      if (iVar1 < 0) {
        Trace("Reset: device reset failed, so attempting rebuild\n");
        D3D_Flush_Texture_Cache();
        iVar1 = D3DAppDestroy(ptVar2);
        if ((iVar1 == 0) ||
           (in_stack_ffffff8c = (char *)Device.hwndApp,
           iVar1 = D3DAppCreateFromHWND(d3dappi.bIsSim,d3dappi.bWindowed,Device.hwndApp), iVar1 == 0
           )) goto LAB_00540687;
      }
      else {
        in_stack_ffffff8c = "Reset: device reset succeeded\n";
        Trace("Reset: device reset succeeded\n");
        D3D_Device_Lost = 0;
      }
    }
    if (D3D_Device_Lost == 0) {
      timeGetTime();
      Trace("Reset: elapsed time %dms\n");
      (*(d3dappi.lpD3DDevice)->lpVtbl->GetBackBuffer)
                (d3dappi.lpD3DDevice,(uint)d3dappi.lpD3DDevice,0,D3DBACKBUFFER_TYPE_MONO,
                 &d3dappi.lpBackBuffer);
      AddTLExecuteBuffer();
      D3DAppISetRenderState();
      CalibrateOcclusionQuery();
LAB_0054063d:
      iVar1 = Net_IsNetGame();
      if (iVar1 != 0) {
        SetEvent(hEvent);
        WaitForSingleObject(unaff_EDI,0xffffffff);
        CloseHandle(unaff_EDI);
        CloseHandle(hEvent);
      }
      return unaff_ESI;
    }
  } while( true );
}
