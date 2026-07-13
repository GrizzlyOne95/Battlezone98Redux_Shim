/*
 * Entry: 004811c4
 * Name: InitCopies
 * Namespace: Global
 * Signature: void InitCopies(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitCopies(void)

{
  int *piVar1;
  
  piVar1 = &copies[0].count;
  freeCopies = 0;
  do {
    freeCopy = freeCopies;
    ((CopyInfo *)(piVar1 + -2))->prev = -1;
    *piVar1 = 0;
    piVar1[1] = 0;
    piVar1[-1] = freeCopy - 1;
    piVar1 = piVar1 + 4;
    freeCopies = freeCopy + 1;
  } while ((uint)freeCopies < 0x1e);
  minFreeCopies = freeCopies;
  return;
}
