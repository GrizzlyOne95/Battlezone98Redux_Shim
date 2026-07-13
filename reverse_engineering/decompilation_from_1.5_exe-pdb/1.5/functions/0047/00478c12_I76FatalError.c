/*
 * Entry: 00478c12
 * Name: I76FatalError
 * Namespace: Global
 * Signature: void I76FatalError(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl I76FatalError(char *param_1)

{
  if (param_1 == (char *)0x0) {
    param_1 = 
    "Sorry, there is not enough memory to continue.\nPlease make sure that you have at least 50MB free on your hard drive and that virtual memory is not disabled."
    ;
  }
  cleanup_before_exit();
  MessageBoxA((HWND)0x0,param_1,"Battlezone",0x10);
                    /* WARNING: Subroutine does not return */
  exit(0x6b);
}
