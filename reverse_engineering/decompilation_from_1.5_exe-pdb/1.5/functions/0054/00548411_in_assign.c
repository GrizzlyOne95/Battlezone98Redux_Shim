/*
 * Entry: 00548411
 * Name: in_assign
 * Namespace: Global
 * Signature: void in_assign(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl in_assign(void)

{
  char cVar1;
  char *pcVar2;
  
  do {
    cVar1 = *inCurrent;
    pcVar2 = inCurrent + 1;
    if (pcVar2 == inLast) {
      return;
    }
    inCurrent = pcVar2;
  } while (cVar1 != '=');
  return;
}
