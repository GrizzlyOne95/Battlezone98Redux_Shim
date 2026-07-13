/*
 * Entry: 005c7c64
 * Name: _UnhandledExceptionFilter@4
 * Namespace: Global
 * Signature: LONG _UnhandledExceptionFilter@4(_EXCEPTION_POINTERS * ExceptionInfo)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LONG _UnhandledExceptionFilter_4(_EXCEPTION_POINTERS *ExceptionInfo)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = UnhandledExceptionFilter(ExceptionInfo);
  return LVar1;
}
