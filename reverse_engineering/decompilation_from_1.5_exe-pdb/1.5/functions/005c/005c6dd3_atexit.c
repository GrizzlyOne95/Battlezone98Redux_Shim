/*
 * Entry: 005c6dd3
 * Name: atexit
 * Namespace: Global
 * Signature: int atexit(_func___cdecl_void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl atexit(_func___cdecl_void *param_1)

{
  _func___cdecl_int *p_Var1;
  
  p_Var1 = _onexit((_func___cdecl_int *)param_1);
  return (p_Var1 != (_func___cdecl_int *)0x0) - 1;
}
