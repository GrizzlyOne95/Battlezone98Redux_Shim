/*
 * Entry: 005c6d18
 * Name: __security_check_cookie
 * Namespace: Global
 * Signature: void __security_check_cookie(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: This is an inlined function */

void __cdecl __security_check_cookie(uint param_1)

{
  uint in_ECX;
  
  if (in_ECX == __security_cookie) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __report_gsfailure();
}
