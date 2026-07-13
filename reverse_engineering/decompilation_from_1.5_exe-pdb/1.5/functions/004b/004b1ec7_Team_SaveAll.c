/*
 * Entry: 004b1ec7
 * Name: Team::SaveAll
 * Namespace: Team
 * Signature: bool SaveAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl Team::SaveAll(_iobuf *param_1)

{
  Team *pTVar1;
  bool bVar2;
  uint local_c;
  Team **local_8;
  
  bVar2 = true;
  if (!missionSave) {
    local_8 = teamList;
    do {
      if (bVar2 == false) {
        return false;
      }
      pTVar1 = *local_8;
      local_c = pTVar1->curScrap ^ 0x33333333;
      bVar2 = ::out(param_1,(long *)&local_c,4,"curScrap");
      if ((((bVar2) && (bVar2 = ::out(param_1,&pTVar1->maxScrap,4,"maxScrap"), bVar2)) &&
          (bVar2 = ::out(param_1,&pTVar1->curPilot,4,"curPilot"), bVar2)) &&
         ((bVar2 = ::out(param_1,&pTVar1->maxPilot,4,"maxPilot"), bVar2 &&
          (bVar2 = ::out(param_1,&pTVar1->dwAllies,4,"dwAllies"), bVar2)))) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      local_8 = local_8 + 1;
    } while ((int)local_8 < 0xb0ce88);
  }
  return bVar2;
}
