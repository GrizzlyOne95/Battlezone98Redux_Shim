/*
 * Entry: 004ba286
 * Name: test_chord
 * Namespace: Global
 * Signature: int test_chord(int param_1, DISCRETE_STATE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl test_chord(int param_1,DISCRETE_STATE *param_2)

{
  long *plVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_1) {
    plVar1 = &param_2->mask;
    do {
      if (plVar1[1] == 1) {
        if ((*plVar1 & *((DISCRETE_STATE *)(plVar1 + -1))->from) != 0) {
          return 0;
        }
      }
      else if ((*plVar1 & *((DISCRETE_STATE *)(plVar1 + -1))->from) == 0) {
        return 0;
      }
      iVar2 = iVar2 + 1;
      plVar1 = plVar1 + 3;
    } while (iVar2 < param_1);
  }
  return 1;
}
