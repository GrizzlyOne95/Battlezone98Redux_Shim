/*
 * Entry: 0041330c
 * Name: BetterMatch
 * Namespace: Global
 * Signature: bool BetterMatch(Geizer * param_1, int param_2, Craft * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl BetterMatch(Geizer *param_1,int param_2,Craft *param_3)

{
  AiCommand AVar1;
  GameObject *pGVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  GameObject *unaff_EBX;
  int unaff_EDI;
  
  pGVar2 = Team::GetSlot(*(Team **)(unaff_EDI + 0x170),(int)param_1);
  if (pGVar2 == (GameObject *)0x0) {
    return false;
  }
  AVar1 = (pGVar2->curCmd).what;
  if (AVar1 != CMD_GO_TO_GEYSER) {
    if (AVar1 != CMD_GO) {
      return false;
    }
    iVar3 = GameObject::GetHandle(unaff_EBX);
    if ((pGVar2->curCmd).who != iVar3) {
      return false;
    }
  }
  if (pGVar2->seqNo < *(int *)(unaff_EDI + 0x150)) {
    pfVar4 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
    pfVar5 = (float *)(**(code **)(unaff_EBX->_padding_ + 0xc))();
    if ((pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
        (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4) <= 225.0) {
      return true;
    }
  }
  return false;
}
