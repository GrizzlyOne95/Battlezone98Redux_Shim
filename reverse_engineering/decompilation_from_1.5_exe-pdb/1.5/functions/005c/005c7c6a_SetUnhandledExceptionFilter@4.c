/*
 * Entry: 005c7c6a
 * Name: _SetUnhandledExceptionFilter@4
 * Namespace: Global
 * Signature: LPTOP_LEVEL_EXCEPTION_FILTER _SetUnhandledExceptionFilter@4(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LPTOP_LEVEL_EXCEPTION_FILTER
_SetUnhandledExceptionFilter_4(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)

{
  LPTOP_LEVEL_EXCEPTION_FILTER pPVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pPVar1 = SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
  return pPVar1;
}
