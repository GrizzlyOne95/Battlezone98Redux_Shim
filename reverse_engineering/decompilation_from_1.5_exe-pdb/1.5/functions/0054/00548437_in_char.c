/*
 * Entry: 00548437
 * Name: in_char
 * Namespace: Global
 * Signature: char in_char(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char __cdecl in_char(void)

{
  char cVar1;
  
  cVar1 = *inCurrent;
  if (inCurrent != inLast) {
    inCurrent = inCurrent + 1;
  }
  return cVar1;
}
