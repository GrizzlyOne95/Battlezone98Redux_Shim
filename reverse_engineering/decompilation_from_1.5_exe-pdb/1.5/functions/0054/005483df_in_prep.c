/*
 * Entry: 005483df
 * Name: in_prep
 * Namespace: Global
 * Signature: void in_prep(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl in_prep(void)

{
  nextLine = inCurrent;
  while( true ) {
    if (inLast <= nextLine) {
      return;
    }
    if (*nextLine == '\r') break;
    nextLine = nextLine + 1;
  }
  *nextLine = '\0';
  return;
}
