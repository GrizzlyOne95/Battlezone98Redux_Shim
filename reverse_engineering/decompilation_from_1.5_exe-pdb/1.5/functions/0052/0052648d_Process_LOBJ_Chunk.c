/*
 * Entry: 0052648d
 * Name: Process_LOBJ_Chunk
 * Namespace: Global
 * Signature: long Process_LOBJ_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_LOBJ_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  VECTOR_3D local_1c;
  IDType local_10;
  float local_c;
  IDType local_8;
  
  local_1c.x = (float)param_1[4].ckSize;
  local_1c.y = *(float *)&param_1[5].ckID;
  local_1c.z = (float)param_1[5].ckSize;
  local_10 = param_1[6].ckID;
  local_c = (float)param_1[6].ckSize;
  local_8 = param_1[7].ckID;
  Add_Light_Source(*(_OBJ76 **)param_2,param_1[1].ckID.longID,(float)param_1[9].ckID,
                   (float)param_1[8].ckSize,&local_1c,(VECTOR_3D *)&local_10.structID);
  *(uint *)(*(int *)param_2 + 0x14) = *(uint *)(*(int *)param_2 + 0x14) | 0x800;
  return 1;
}
