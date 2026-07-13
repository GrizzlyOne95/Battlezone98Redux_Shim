/*
 * Entry: 0045d15e
 * Name: ScavengerProcess::Verify_Or_Request_Escorts
 * Namespace: ScavengerProcess
 * Signature: void Verify_Or_Request_Escorts(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::Verify_Or_Request_Escorts(ScavengerProcess *this)

{
  int iVar1;
  tag_c_linked_list *ptVar2;
  void *pvVar3;
  GameObject *pGVar4;
  int iVar5;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && (this->team != 1)) {
    ptVar2 = this->my_escorts;
    iVar1 = 0;
    if ((ptVar2 != (tag_c_linked_list *)0x0) && (0 < ptVar2->count)) {
      do {
        pvVar3 = C_Linked_List_Return_Data_By_Number(ptVar2,iVar1);
        pGVar4 = GameObjectHandle::GetObj((int)pvVar3);
        if (pGVar4 == (GameObject *)0x0) {
LAB_0045d1e7:
          Decrement_Escort_Count(this,(int)pvVar3);
        }
        else {
          if ((pGVar4->curCmd).what != CMD_FOLLOW) {
LAB_0045d1c6:
            if ((pGVar4->nextCmd).what == CMD_FOLLOW) {
              if (this->craft == (Scavenger *)0x0) {
                iVar5 = 0;
              }
              else {
                iVar5 = GameObject::GetHandle((GameObject *)this->craft);
              }
              if ((pGVar4->nextCmd).who == iVar5) goto LAB_0045d1f1;
            }
            goto LAB_0045d1e7;
          }
          if (this->craft == (Scavenger *)0x0) {
            iVar5 = 0;
          }
          else {
            iVar5 = GameObject::GetHandle((GameObject *)this->craft);
          }
          if ((pGVar4->curCmd).who != iVar5) goto LAB_0045d1c6;
        }
LAB_0045d1f1:
        ptVar2 = this->my_escorts;
        iVar1 = iVar1 + 1;
      } while (iVar1 < ptVar2->count);
    }
  }
  return;
}
