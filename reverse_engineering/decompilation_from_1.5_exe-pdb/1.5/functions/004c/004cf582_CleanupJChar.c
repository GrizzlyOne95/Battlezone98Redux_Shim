/*
 * Entry: 004cf582
 * Name: CleanupJChar
 * Namespace: Global
 * Signature: void CleanupJChar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CleanupJChar(void)

{
  int iVar1;
  
  iVar1 = IsJapanese();
  if (iVar1 != 0) {
    operator_delete__(charMap);
    charMap = (short *)0x0;
    charCount = 0;
  }
  return;
}
