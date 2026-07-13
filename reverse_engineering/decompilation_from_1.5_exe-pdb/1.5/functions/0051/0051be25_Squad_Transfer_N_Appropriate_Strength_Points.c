/*
 * Entry: 0051be25
 * Name: Squad_Transfer_N_Appropriate_Strength_Points
 * Namespace: Global
 * Signature: int Squad_Transfer_N_Appropriate_Strength_Points(tag_team * param_1, tag_squad * param_2, tag_squad * param_3, int param_4, int * param_5, Goal * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Squad_Transfer_N_Appropriate_Strength_Points
          (tag_team *param_1,tag_squad *param_2,tag_squad *param_3,int param_4,int *param_5,
          Goal *param_6)

{
  bool bVar1;
  tagUNIT *ptVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  local_c = 0;
  bVar1 = false;
  local_8 = 0;
  *param_5 = 0;
  while ((0 < param_4 && (!bVar1))) {
    ptVar2 = C_Linked_List_Return_Data_By_Number(&param_2->my_units,local_8);
    if (ptVar2 == (tagUNIT *)0x0) {
      bVar1 = true;
    }
    else {
      iVar3 = (**(code **)(param_6->_padding_ + 0x20))(ptVar2);
      bVar1 = false;
      if (iVar3 == 0) {
        local_8 = local_8 + 1;
      }
      else {
        Squad_Remove_Unit(param_2,ptVar2,param_1);
        Squad_Add_Unit(param_3,ptVar2,param_1);
        iVar3 = AI_Match_Get_Unit_Strength(ptVar2,param_1);
        param_4 = param_4 - iVar3;
        local_c = local_c + iVar3;
        *param_5 = *param_5 + 1;
      }
    }
  }
  return local_c;
}
