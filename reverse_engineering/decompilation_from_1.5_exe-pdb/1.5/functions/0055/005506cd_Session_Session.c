/*
 * Entry: 005506cd
 * Name: Session::Session
 * Namespace: Session
 * Signature: Session * Session(Session * this, dp_session_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session * __thiscall Session::Session(Session *this,dp_session_t *param_1)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  int iVar4;
  Session *pSVar5;
  
  pSVar5 = this;
  for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
    uVar1 = param_1->adrMaster[0];
    uVar2 = param_1->adrMaster[1];
    uVar3 = param_1->adrMaster[2];
    (pSVar5->dp_session).field0_0x0 = param_1->field0_0x0;
    (pSVar5->dp_session).adrMaster[0] = uVar1;
    (pSVar5->dp_session).adrMaster[1] = uVar2;
    (pSVar5->dp_session).adrMaster[2] = uVar3;
    param_1 = (dp_session_t *)(param_1->adrMaster + 3);
    pSVar5 = (Session *)((pSVar5->dp_session).adrMaster + 3);
  }
  uVar1 = param_1->adrMaster[0];
  (pSVar5->dp_session).field0_0x0 = param_1->field0_0x0;
  (pSVar5->dp_session).adrMaster[0] = uVar1;
  (pSVar5->dp_session).adrMaster[1] = param_1->adrMaster[1];
  this->mark = 100;
  this->bBanned = false;
  return this;
}
