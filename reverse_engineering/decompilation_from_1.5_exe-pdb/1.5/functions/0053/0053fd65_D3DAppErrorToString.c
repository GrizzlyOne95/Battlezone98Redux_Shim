/*
 * Entry: 0053fd65
 * Name: D3DAppErrorToString
 * Namespace: Global
 * Signature: char * D3DAppErrorToString(T_HRESULT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl D3DAppErrorToString(T_HRESULT param_1)

{
  char *pcVar1;
  
  pcVar1 = DXGetErrorDescriptionA(param_1);
  return pcVar1;
}
