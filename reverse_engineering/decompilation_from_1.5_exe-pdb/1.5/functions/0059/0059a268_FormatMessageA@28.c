/*
 * Entry: 0059a268
 * Name: _FormatMessageA@28
 * Namespace: Global
 * Signature: DWORD _FormatMessageA@28(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPSTR lpBuffer, DWORD nSize, va_list * Arguments)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _FormatMessageA_28(DWORD dwFlags,LPCVOID lpSource,DWORD dwMessageId,DWORD dwLanguageId,
                        LPSTR lpBuffer,DWORD nSize,va_list *Arguments)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a268. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = FormatMessageA(dwFlags,lpSource,dwMessageId,dwLanguageId,lpBuffer,nSize,Arguments);
  return DVar1;
}
