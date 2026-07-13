/*
 * Entry: 0049bfc9
 * Name: GeoCache_AddRep
 * Namespace: Global
 * Signature: int GeoCache_AddRep(_OBJ76 * param_1, char * param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GeoCache_AddRep(_OBJ76 *param_1,char *param_2,long param_3,long param_4)

{
  int iVar1;
  _REP_INFO *p_Var2;
  int iVar3;
  _GEOMETRY *p_Var4;
  uint local_c;
  undefined4 local_8;
  
  if ((param_2 == (char *)0x0) || (iVar1 = _strnicmp(param_2,"null",4), iVar1 == 0)) {
    if ((param_3 == 0) && (param_4 == 0)) {
      param_1->geom = (_GEOMETRY *)0x0;
      (param_1->reps).repNum = 0;
    }
    return 0;
  }
  iVar1 = (param_1->reps).repCount;
  if (iVar1 == 0) {
    (param_1->reps).repSlots = 10;
    p_Var2 = malloc(0xa0);
  }
  else {
    iVar3 = (param_1->reps).repSlots;
    if (iVar1 != iVar3) goto LAB_0049c034;
    iVar3 = iVar3 + 10;
    (param_1->reps).repSlots = iVar3;
    p_Var2 = realloc((param_1->reps).reps,iVar3 * 0x10);
  }
  (param_1->reps).reps = p_Var2;
LAB_0049c034:
  iVar1 = (param_1->reps).repCount;
  p_Var2 = (param_1->reps).reps + iVar1;
  (param_1->reps).repCount = iVar1 + 1;
  p_Var2->repNum = param_3 << 0x10 | param_4;
  SplitPrjFile(param_2,(long64 *)&local_c,(long *)&param_2);
  p_Var4 = Geom_Load(CONCAT44(local_8,local_c));
  p_Var2->geom = p_Var4;
  if (p_Var4 == (_GEOMETRY *)0x0) {
    DEBUG_printf("Missing geometry \"%.8s\"\n");
  }
  *(uint *)&p_Var2->id = local_c;
  *(undefined4 *)((int)&p_Var2->id + 4) = local_8;
  if ((param_3 == 0) && (param_4 == 0)) {
    param_1->geom = p_Var2->geom;
    (param_1->reps).repNum = 0;
  }
  return (uint)(p_Var2->geom != (_GEOMETRY *)0x0);
}
