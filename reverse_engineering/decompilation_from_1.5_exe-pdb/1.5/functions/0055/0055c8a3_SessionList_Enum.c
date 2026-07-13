/*
 * Entry: 0055c8a3
 * Name: SessionList::Enum
 * Namespace: SessionList
 * Signature: void Enum(SessionList * this, dp_session_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::Enum(SessionList *this,dp_session_t *param_1)

{
  Session *pSVar1;
  int iVar2;
  
  AddModify(this,param_1);
  pSVar1 = FindSession(this,this->dp_karma_selected);
  if (param_1 != (dp_session_t *)0x0) {
    if (this->bWaitSes == false) {
      this->bFoundSes = true;
    }
    else {
      this->bFoundSes = this->dp_karma_selected == (param_1->field4_0xf).karma;
    }
    iVar2 = ((int)(param_1->field5_0x11).maxPlayers >> 1) -
            (int)(param_1->field6_0x13).currentPlayers;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if ((((this->dp_karma_selected == 0) ||
         (((pSVar1 != (Session *)0x0 && ((pSVar1->dp_session).field6_0x13.currentPlayers < 2)) &&
          (((pSVar1->dp_session).dwUser1 & 2) != 0)))) &&
        (((param_1->dwUser1 & 2) != 0 &&
         ((param_1->field6_0x13).currentPlayers < (param_1->field5_0x11).maxPlayers)))) &&
       ((iVar2 < this->optFoundNumber ||
        ((iVar2 == this->optFoundNumber &&
         (((param_1->field4_0xf).karma < this->dp_karma_found || (this->dp_karma_found == 0))))))))
    {
      this->dp_karma_found = (short)param_1->field4_0xf;
      this->optFoundNumber = iVar2;
    }
  }
  return;
}
