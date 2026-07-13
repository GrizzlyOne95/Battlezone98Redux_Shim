/*
 * Entry: 00409650
 * Name: GetClosestScrapDropoff
 * Namespace: Global
 * Signature: GameObject * GetClosestScrapDropoff(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestScrapDropoff(GameObject *param_1)

{
  float fVar1;
  char cVar2;
  GameObject *pGVar3;
  float *pfVar4;
  float *pfVar5;
  GameObject *pGVar6;
  
  pGVar3 = Team::GetSlot(param_1->teamList,1);
  if (pGVar3 != (GameObject *)0x0) {
    cVar2 = (**(code **)(pGVar3->_padding_ + 100))();
    if (cVar2 == '\0') {
      pGVar3 = (GameObject *)0x0;
    }
    if (pGVar3 != (GameObject *)0x0) {
      pfVar4 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
      pfVar5 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
      fVar1 = (pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
              (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4);
      goto LAB_004096aa;
    }
  }
  fVar1 = 1e+30;
LAB_004096aa:
  pGVar6 = GetClosestSilo(param_1,fVar1);
  if (pGVar6 == (GameObject *)0x0) {
    pGVar6 = pGVar3;
  }
  return pGVar6;
}
