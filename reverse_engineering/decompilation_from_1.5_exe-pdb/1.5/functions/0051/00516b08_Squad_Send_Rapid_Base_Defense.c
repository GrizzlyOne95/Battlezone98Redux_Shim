/*
 * Entry: 00516b08
 * Name: Squad_Send_Rapid_Base_Defense
 * Namespace: Global
 * Signature: void Squad_Send_Rapid_Base_Defense(tag_squad * param_1, Mapgrid_Goal * param_2, GameObject * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Squad_Send_Rapid_Base_Defense(tag_squad *param_1,Mapgrid_Goal *param_2,GameObject *param_3)

{
  GameObject *this;
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (param_1->my_units).count;
  if ((iVar2 != 0) && (iVar3 = 0, 0 < iVar2)) {
    do {
      puVar1 = C_Linked_List_Return_Data_By_Number(&param_1->my_units,iVar3);
      this = (GameObject *)*puVar1;
      iVar2 = (**(code **)this->_padding_)();
      if (*(int *)(iVar2 + 0x20) == 0x57494e47) {
        GameObject::SetCommand(this,CMD_ATTACK,param_3);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->my_units).count);
  }
  return;
}
