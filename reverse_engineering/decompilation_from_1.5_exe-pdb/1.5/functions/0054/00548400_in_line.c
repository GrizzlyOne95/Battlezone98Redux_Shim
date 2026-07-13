/*
 * Entry: 00548400
 * Name: in_line
 * Namespace: Global
 * Signature: void in_line(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl in_line(void)

{
  char *pcVar1;
  
  pcVar1 = nextLine;
  *nextLine = '\r';
  inCurrent = pcVar1 + 2;
  return;
}
