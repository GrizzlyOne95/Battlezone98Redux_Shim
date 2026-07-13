/*
 * Entry: 0049b45d
 * Name: GeoCache_Delete
 * Namespace: Global
 * Signature: int GeoCache_Delete(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GeoCache_Delete(_OBJ76 *param_1)

{
  _REPS *p_Var1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  p_Var1 = &param_1->reps;
  iVar4 = 0;
  if (0 < p_Var1->repCount) {
    iVar3 = 0;
    do {
      piVar2 = *(int **)((int)&((param_1->reps).reps)->geom + iVar3);
      if (piVar2 != (int *)0x0) {
        piVar2 = (int *)(*piVar2 + 0xc);
        *piVar2 = *piVar2 + -1;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x10;
    } while (iVar4 < p_Var1->repCount);
  }
  free((param_1->reps).reps);
  p_Var1->repCount = 0;
  (param_1->reps).repSlots = 0;
  (param_1->reps).repNum = 0;
  (param_1->reps).reps = (_REP_INFO *)0x0;
  param_1->geom = (_GEOMETRY *)0x0;
  return 1;
}
