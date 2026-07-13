/*
 * Entry: 0049b3ef
 * Name: SplitPrjFile
 * Namespace: Global
 * Signature: void SplitPrjFile(char * param_1, long64 * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SplitPrjFile(char *param_1,long64 *param_2,long *param_3)

{
  int iVar1;
  
  iVar1 = 8;
  do {
    if ((char)*(long *)param_1 == '.') {
      *(char *)param_2 = '\0';
    }
    else {
      *(char *)param_2 = (char)*(long *)param_1;
      param_1 = (char *)((int)param_1 + 1);
    }
    param_2 = (long64 *)((int)param_2 + 1);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *param_3 = *(long *)param_1;
  return;
}
