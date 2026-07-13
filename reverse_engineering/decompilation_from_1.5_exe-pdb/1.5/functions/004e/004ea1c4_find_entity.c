/*
 * Entry: 004ea1c4
 * Name: find_entity
 * Namespace: Global
 * Signature: tagENTITY * find_entity(long64 param_1, short param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl find_entity(long64 param_1,short param_2)

{
  _OBJ76 *p_Var1;
  tagENTITY *ptVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < world_count) {
    ptVar2 = world;
    do {
      p_Var1 = ptVar2->obj76;
      if ((((p_Var1 != (_OBJ76 *)0x0) && ((uint)ptVar2->seqNo == (int)param_2)) &&
          ((int)p_Var1->id == (int)param_1)) && (*(int *)((int)&p_Var1->id + 4) == param_1._4_4_)) {
        return ptVar2;
      }
      iVar3 = iVar3 + 1;
      ptVar2 = ptVar2 + 1;
    } while (iVar3 < world_count);
  }
  return (tagENTITY *)0x0;
}
