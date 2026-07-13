/*
 * Entry: 004bf08b
 * Name: ChunkEffect::FullFragmentObject
 * Namespace: ChunkEffect
 * Signature: void FullFragmentObject(ChunkEffect * this, _OBJ76 * param_1, VECTOR_3D param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ChunkEffect::FullFragmentObject(ChunkEffect *this,_OBJ76 *param_1,VECTOR_3D param_2,bool param_3)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  VECTOR_3D *pVVar3;
  Chunk *pCVar4;
  VECTOR_3D local_14;
  ChunkEffect *local_8;
  
  local_8 = this;
  if (depth == 0) {
    pVVar3 = obj_get_world_position(&local_14,param_1);
    origin.x = pVVar3->x;
    origin.y = pVVar3->y;
    origin.z = pVVar3->z;
  }
  depth = depth + 1;
  p_Var1 = param_1;
  while (param_1 = p_Var1, param_1 != (_OBJ76 *)0x0) {
    if (param_1->child != (_OBJ76 *)0x0) {
      FullFragmentObject(local_8,param_1->child,param_2,param_3);
    }
    p_Var1 = param_1->sibling;
    if ((param_1->parent != (_OBJ76 *)0x0) &&
       (pCVar4 = CreateChunk(local_8,param_1,param_2,param_3), pCVar4 != (Chunk *)0x0)) {
      p_Var2 = pCVar4->obj;
      (pCVar4->veloc).x = ((float)(p_Var2->transform).posit_x - origin.x) * 2.0 + (pCVar4->veloc).x;
      (pCVar4->veloc).y = ((float)(p_Var2->transform).posit_y - origin.y) + (pCVar4->veloc).y;
      (pCVar4->veloc).z = ((float)(p_Var2->transform).posit_z - origin.z) * 2.0 + (pCVar4->veloc).z;
    }
  }
  depth = depth + -1;
  return;
}
