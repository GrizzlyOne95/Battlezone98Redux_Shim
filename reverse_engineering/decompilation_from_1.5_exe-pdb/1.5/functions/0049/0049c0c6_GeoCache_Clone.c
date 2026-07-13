/*
 * Entry: 0049c0c6
 * Name: GeoCache_Clone
 * Namespace: Global
 * Signature: int GeoCache_Clone(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GeoCache_Clone(_OBJ76 *param_1,_OBJ76 *param_2)

{
  _OBJ76 *p_Var1;
  _REP_INFO *p_Var2;
  _GEOMETRY *p_Var3;
  char *pcVar4;
  char *pcVar5;
  int local_8;
  
  p_Var1 = param_2;
  (param_2->reps).repCount = (param_1->reps).repCount;
  (param_2->reps).repSlots = (param_1->reps).repSlots;
  p_Var2 = malloc((param_1->reps).repSlots << 4);
  (param_2->reps).reps = p_Var2;
  (param_2->reps).repNum = (param_1->reps).repNum;
  local_8 = 0;
  if (0 < (param_2->reps).repCount) {
    param_2 = (_OBJ76 *)0x0;
    do {
      pcVar4 = (param_2->tex_info).group + (int)&(param_1->reps).reps[-8].id;
      pcVar5 = (param_2->tex_info).group + (int)&(p_Var1->reps).reps[-8].id;
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
      p_Var3 = Geom_Load(*(long64 *)(pcVar4 + 8));
      local_8 = local_8 + 1;
      param_2 = (_OBJ76 *)&param_2->gravestone;
      *(_GEOMETRY **)(pcVar5 + 4) = p_Var3;
      *(undefined4 *)(pcVar5 + 8) = *(undefined4 *)(pcVar4 + 8);
      *(undefined4 *)(pcVar5 + 0xc) = *(undefined4 *)(pcVar4 + 0xc);
    } while (local_8 < (p_Var1->reps).repCount);
  }
  p_Var1->geom = param_1->geom;
  return 1;
}
