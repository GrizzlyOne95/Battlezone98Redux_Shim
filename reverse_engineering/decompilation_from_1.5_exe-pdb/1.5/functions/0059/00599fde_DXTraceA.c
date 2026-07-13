/*
 * Entry: 00599fde
 * Name: DXTraceA
 * Namespace: Global
 * Signature: T_HRESULT DXTraceA(char * param_1, ulong param_2, T_HRESULT param_3, char * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl
DXTraceA(char *param_1,ulong param_2,undefined4 param_3,char *param_4,int param_5)

{
  HWND hWnd;
  int iVar1;
  char *lpText;
  char *lpCaption;
  UINT uType;
  uint local_1248;
  char local_1244 [1024];
  char local_e44 [3000];
  char local_28c [260];
  char local_188 [256];
  char local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  StringCchPrintfA(local_88,0x80,"%ld");
  if (param_1 != (char *)0x0) {
    StringCchPrintfA(local_e44,3000,"%s(%s): ");
    OutputDebugStringA(local_e44);
  }
  local_1248 = 0;
  StringCchLengthA(param_4,0x400,&local_1248);
  if (local_1248 != 0) {
    OutputDebugStringA(param_4);
    OutputDebugStringA(" ");
  }
  DXGetErrorStringA(param_3);
  StringCchPrintfA(local_188,0x100,"%s (0x%0.8x)");
  StringCchPrintfA(local_e44,3000,"hr=%s");
  OutputDebugStringA(local_e44);
  OutputDebugStringA("\n");
  if (param_5 != 0) {
    StringCchCopyA(local_28c,0x104,"");
    if (param_1 != (char *)0x0) {
      StringCchCopyA(local_28c,0x104,param_1);
    }
    StringCchCopyA(local_1244,0x400,"");
    if (local_1248 != 0) {
      StringCchPrintfA(local_1244,0x400,"Calling: %s\n");
    }
    StringCchPrintfA(local_e44,3000,
                     "File: %S\nLine: %s\nError Code: %s\n%sDo you want to debug the application?");
    uType = 0x14;
    lpCaption = "Unexpected error encountered";
    lpText = local_e44;
    hWnd = GetForegroundWindow();
    iVar1 = MessageBoxA(hWnd,lpText,lpCaption,uType);
    if (iVar1 == 6) {
      DebugBreak();
    }
  }
  return param_3;
}
