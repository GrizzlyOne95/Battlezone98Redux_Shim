/*
 * Entry: 0050ecb8
 * Name: Escort_Goal::Execute_Task
 * Namespace: Escort_Goal
 * Signature: void Execute_Task(Escort_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Escort_Goal::Execute_Task(Escort_Goal *this)

{
  GameObject *pGVar1;
  tagUNIT *ptVar2;
  GameObject *pGVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  if ((((this->_padding_ == 0) && (this->_padding_ == 0)) && (iVar4 = this->_padding_, iVar4 != 0))
     && (pGVar1 = this->damsel_in_distress, 0 < *(int *)(iVar4 + 0x14))) {
    do {
      ptVar2 = C_Linked_List_Return_Data_By_Number((tag_c_linked_list *)(iVar4 + 0xc),iVar5);
      pGVar3 = GameObjectHandle::GetObj(ptVar2->handle);
      if (((pGVar3 == (GameObject *)0x0) || (pGVar3->aiProcess == (AiProcess *)0x0)) ||
         (iVar4 = (**(code **)(pGVar3->_padding_ + 4))(), iVar4 != this->the_team->team_ID)) {
        Squad_Remove_Unit((tag_squad *)this->_padding_,ptVar2,this->the_team);
      }
      else {
        GameObject::SetCommand((GameObject *)ptVar2->id,CMD_FOLLOW,pGVar1);
        (**(code **)(this->_padding_ + 0x24))(ptVar2);
      }
      iVar4 = this->_padding_;
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(iVar4 + 0x14));
  }
  return;
}
