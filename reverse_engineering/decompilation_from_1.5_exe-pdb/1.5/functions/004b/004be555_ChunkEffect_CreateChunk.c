/*
 * Entry: 004be555
 * Name: ChunkEffect::CreateChunk
 * Namespace: ChunkEffect
 * Signature: Chunk * CreateChunk(ChunkEffect * this, _OBJ76 * param_1, VECTOR_3D param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Chunk * __thiscall
ChunkEffect::CreateChunk(ChunkEffect *this,_OBJ76 *param_1,VECTOR_3D param_2,bool param_3)

{
  Chunk *pCVar1;
  MAT_3D *pMVar2;
  int iVar3;
  float *pfVar4;
  MAT_3D local_88;
  float local_48 [16];
  ChunkEffect *local_8;
  
  local_8 = this;
  if (param_1->geom != (_GEOMETRY *)0x0) {
    iVar3 = this->chunkCount;
    if (iVar3 < 0x400) {
      pCVar1 = this->chunkList + iVar3;
      this->chunkCount = iVar3 + 1;
      ClassDelete(param_1);
      param_1->class_id = CLASS_ID_CHUNK;
      pMVar2 = obj_rel_parent_matrix(&local_88,param_1,(_OBJ76 *)0x0);
      pfVar4 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pfVar4 = pMVar2->right_x;
        pMVar2 = (MAT_3D *)&pMVar2->right_y;
        pfVar4 = pfVar4 + 1;
      }
      pfVar4 = local_48;
      pMVar2 = &param_1->transform;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        pMVar2->right_x = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pMVar2 = (MAT_3D *)&pMVar2->right_y;
      }
      param_1->flags = -(uint)param_3 & 8;
      remove_obj_from_tree(param_1);
      add_obj_to_tree(param_1,local_8->ent->obj76);
      pCVar1->obj = param_1;
      pCVar1->timer = 0.0;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      (pCVar1->veloc).x = Pseudo_Rand_Number[Rand_Counter] * 10.0 + param_2.x;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      (pCVar1->veloc).y = Pseudo_Rand_Number[Rand_Counter] * 10.0 + param_2.y + 5.0;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      (pCVar1->veloc).z = Pseudo_Rand_Number[Rand_Counter] * 10.0 + param_2.z;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      (pCVar1->omega).x = Pseudo_Rand_Number[Rand_Counter] * 5.0;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      (pCVar1->omega).y = Pseudo_Rand_Number[Rand_Counter] * 5.0;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      (pCVar1->omega).z = Pseudo_Rand_Number[Rand_Counter] * 5.0;
      return pCVar1;
    }
  }
  remove_obj(param_1,".\\fun3d\\ChunkEffect.cpp");
  return (Chunk *)0x0;
}
