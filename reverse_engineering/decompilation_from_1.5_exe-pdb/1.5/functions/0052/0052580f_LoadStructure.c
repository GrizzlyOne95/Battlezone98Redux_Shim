/*
 * Entry: 0052580f
 * Name: LoadStructure
 * Namespace: Global
 * Signature: long LoadStructure(StructObjectType * param_1, ENTITY_LOADER * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl LoadStructure(StructObjectType *param_1,ENTITY_LOADER *param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = ReadBWD2File(param_3,SDFChunkDefs,7,param_2);
  return iVar1;
}
