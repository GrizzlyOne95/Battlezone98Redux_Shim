/*
 * Entry: 005c7958
 * Name: __CxxSetUnhandledExceptionFilter
 * Namespace: Global
 * Signature: int __CxxSetUnhandledExceptionFilter(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl __CxxSetUnhandledExceptionFilter(void)

{
  SetUnhandledExceptionFilter(__CxxUnhandledExceptionFilter);
  return 0;
}
