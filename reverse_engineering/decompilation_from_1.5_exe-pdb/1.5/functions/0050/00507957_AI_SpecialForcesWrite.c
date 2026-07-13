/*
 * Entry: 00507957
 * Name: AI_SpecialForcesWrite
 * Namespace: Global
 * Signature: void AI_SpecialForcesWrite(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpecialForcesWrite(_iobuf *param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  int local_4;
  
  Debug_Assert((int)param_1,0x57b,".\\Schedule\\Ai.cpp","file");
  local_4 = 0;
  if (0 < special_forces_groups.count) {
    do {
      puVar1 = C_Linked_List_Return_Data_By_Number(&special_forces_groups,local_4);
      Debug_Assert((int)puVar1,0x582,".\\Schedule\\Ai.cpp","sf");
      fprintf((FILE *)param_1,"DefineSpecialForces ( %d %d )\n",*puVar1,puVar1[6]);
      fprintf((FILE *)param_1,"{\n");
      iVar3 = 0;
      if (0 < (int)puVar1[3]) {
        do {
          pvVar2 = C_Linked_List_Return_Data_By_Number((tag_c_linked_list *)(puVar1 + 1),iVar3);
          fprintf((FILE *)param_1,"  %d",pvVar2);
          iVar3 = iVar3 + 1;
        } while (iVar3 < (int)puVar1[3]);
      }
      fprintf((FILE *)param_1,"\n");
      fprintf((FILE *)param_1,"}\n");
      fprintf((FILE *)param_1,"\n");
      local_4 = local_4 + 1;
    } while (local_4 < special_forces_groups.count);
  }
  return;
}
