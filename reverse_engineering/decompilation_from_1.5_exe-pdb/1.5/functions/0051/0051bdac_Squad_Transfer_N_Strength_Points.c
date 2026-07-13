/*
 * Entry: 0051bdac
 * Name: Squad_Transfer_N_Strength_Points
 * Namespace: Global
 * Signature: int Squad_Transfer_N_Strength_Points(tag_team * param_1, tag_squad * param_2, tag_squad * param_3, int param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Squad_Transfer_N_Strength_Points
          (tag_team *param_1,tag_squad *param_2,tag_squad *param_3,int param_4,int *param_5)

{
  tagUNIT *ptVar1;
  int iVar2;
  bool bVar3;
  int local_8;
  
  local_8 = 0;
  bVar3 = false;
  *param_5 = 0;
  while ((0 < param_4 && (!bVar3))) {
    ptVar1 = C_Linked_List_Return_Data_By_Number(&param_2->my_units,0);
    bVar3 = ptVar1 == (tagUNIT *)0x0;
    if (!bVar3) {
      Squad_Remove_Unit(param_2,ptVar1,param_1);
      Squad_Add_Unit(param_3,ptVar1,param_1);
      iVar2 = AI_Match_Get_Unit_Strength(ptVar1,param_1);
      param_4 = param_4 - iVar2;
      local_8 = local_8 + iVar2;
      *param_5 = *param_5 + 1;
    }
  }
  return local_8;
}
