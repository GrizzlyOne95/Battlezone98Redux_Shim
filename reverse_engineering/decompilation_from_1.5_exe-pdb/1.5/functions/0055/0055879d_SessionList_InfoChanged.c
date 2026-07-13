/*
 * Entry: 0055879d
 * Name: SessionList::InfoChanged
 * Namespace: SessionList
 * Signature: bool InfoChanged(SessionList * this, Session * param_1, dp_session_t * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SessionList::InfoChanged(SessionList *this,Session *param_1,dp_session_t *param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = 0x5f;
  bVar2 = true;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar2 = (param_1->dp_session).field0_0x0.dummy == (param_2->field0_0x0).dummy;
    param_1 = (Session *)(param_1->dp_session).adrMaster;
    param_2 = (dp_session_t *)param_2->adrMaster;
  } while (bVar2);
  return !bVar2;
}
