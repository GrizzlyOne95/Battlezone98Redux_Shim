/*
 * Entry: 005c752b
 * Name: WinMainCRTStartup
 * Namespace: Global
 * Signature: int WinMainCRTStartup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl WinMainCRTStartup(void)

{
  int iVar1;
  
  __security_init_cookie();
  iVar1 = __tmainCRTStartup();
  return iVar1;
}
