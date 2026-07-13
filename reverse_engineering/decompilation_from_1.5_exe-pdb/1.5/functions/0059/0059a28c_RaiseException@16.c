/*
 * Entry: 0059a28c
 * Name: _RaiseException@16
 * Namespace: Global
 * Signature: void _RaiseException@16(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, ULONG_PTR * lpArguments)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _RaiseException_16(DWORD dwExceptionCode,DWORD dwExceptionFlags,DWORD nNumberOfArguments,
                       ULONG_PTR *lpArguments)

{
                    /* WARNING: Could not recover jumptable at 0x0059a28c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RaiseException(dwExceptionCode,dwExceptionFlags,nNumberOfArguments,lpArguments);
  return;
}
