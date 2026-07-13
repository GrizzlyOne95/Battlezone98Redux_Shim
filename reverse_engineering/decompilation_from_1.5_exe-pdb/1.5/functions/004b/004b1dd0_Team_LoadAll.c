/*
 * Entry: 004b1dd0
 * Name: Team::LoadAll
 * Namespace: Team
 * Signature: bool LoadAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl Team::LoadAll(_iobuf *param_1)

{
  Team *pTVar1;
  bool bVar2;
  uint local_10;
  int local_c;
  int local_8;
  
  bVar2 = true;
  if ((!missionSave) && (0x400 < version)) {
    local_8 = 0;
    local_c = (uint)(0x40f < version) * 8 + 8;
    if (local_c != 0) {
      do {
        if (bVar2 == false) {
          return false;
        }
        pTVar1 = teamList[local_8];
        bVar2 = ::in(param_1,(long *)&local_10,4);
        pTVar1->curScrap = local_10 ^ 0x33333333;
        if ((((bVar2) && (bVar2 = ::in(param_1,&pTVar1->maxScrap,4), bVar2)) &&
            (bVar2 = ::in(param_1,&pTVar1->curPilot,4), bVar2)) &&
           ((bVar2 = ::in(param_1,&pTVar1->maxPilot,4), bVar2 &&
            (bVar2 = ::in(param_1,&pTVar1->dwAllies,4), bVar2)))) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
        local_8 = local_8 + 1;
      } while (local_8 < local_c);
    }
  }
  return bVar2;
}
