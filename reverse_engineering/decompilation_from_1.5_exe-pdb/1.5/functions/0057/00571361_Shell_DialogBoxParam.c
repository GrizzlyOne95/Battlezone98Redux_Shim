/*
 * Entry: 00571361
 * Name: Shell_DialogBoxParam
 * Namespace: Global
 * Signature: int Shell_DialogBoxParam(HINSTANCE__ * param_1, char * param_2, HWND__ * param_3, _func___cdecl_int_HWND___ptr_uint_uint_long * param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Shell_DialogBoxParam
          (HINSTANCE__ *param_1,char *param_2,HWND__ *param_3,
          _func___cdecl_int_HWND___ptr_uint_uint_long *param_4,long param_5)

{
  HWND__ *pHVar1;
  int iVar2;
  BOOL BVar3;
  tagMSG local_20;
  
  pHVar1 = hDialog;
  nDialogResult = 0;
  hDialog = (HWND__ *)
            CreateDialogParamA((HINSTANCE)param_1,param_2,(HWND)param_3,(DLGPROC)param_4,param_5);
  ShowWindow((HWND)hDialog,5);
  SetFocus((HWND)hDialog);
  do {
    while( true ) {
      do {
        if (hDialog == (HWND__ *)0x0) {
          hDialog = pHVar1;
          return nDialogResult;
        }
        if ((Device.ShutDownReq != 0) || (iVar2 = GetRunning(), iVar2 == 10)) {
          nShellMode = 0;
          Shell_EndDialog(hDialog,1);
          SetRunning(10);
          hDialog = pHVar1;
          return nDialogResult;
        }
        BVar3 = GetMessageA(&local_20,(HWND)0x0,0,0);
      } while (BVar3 == 0);
      if (local_20.message != 0x102) break;
      if (local_20.wParam == 0xd) {
        SendMessageA((HWND)hDialog,0x111,1,0);
      }
      else {
LAB_0057143b:
        BVar3 = IsDialogMessageA((HWND)hDialog,&local_20);
        if ((BVar3 == 0) || ((bWaitForKey != 0 && (local_20.message - 0x100 < 10)))) {
          TranslateMessage(&local_20);
          DispatchMessageA(&local_20);
        }
      }
    }
    if ((local_20.message != 0x104) || (local_20.wParam != 0xd)) goto LAB_0057143b;
    if (useD3D != 0) {
      UseDDraw = (int)(UseDDraw == 0);
      (*Device.VideoMode.ChangeMode)(&Device,ResolutionMode);
    }
  } while( true );
}
