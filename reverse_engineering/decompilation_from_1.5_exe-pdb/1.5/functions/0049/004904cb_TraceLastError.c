/*
 * Entry: 004904cb
 * Name: TraceLastError
 * Namespace: Global
 * Signature: void TraceLastError(T_HRESULT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TraceLastError(DWORD param_1)

{
  CHAR local_8 [4];
  
  FormatMessageA(0x1300,(LPCVOID)0x0,param_1,0x400,local_8,0,(va_list *)0x0);
  return;
}
