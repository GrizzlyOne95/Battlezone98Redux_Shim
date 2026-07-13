/*
 * Entry: 004ae759
 * Name: BestDropoff
 * Namespace: Global
 * Signature: GameObject * BestDropoff(Scavenger * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl BestDropoff(Scavenger *param_1)

{
  char cVar1;
  GameObject *pGVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  
  pGVar2 = GetClosestScrapDropoff((GameObject *)param_1);
  if (pGVar2 != (GameObject *)0x0) {
    pfVar3 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
    pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
    if ((1600.0 < (pfVar4[2] - pfVar3[2]) * (pfVar4[2] - pfVar3[2]) +
                  (*pfVar4 - *pfVar3) * (*pfVar4 - *pfVar3)) ||
       ((iVar5 = (**(code **)pGVar2->_padding_)(), *(int *)(iVar5 + 0x20) == 0x52435943 &&
        (cVar1 = (**(code **)(pGVar2->_padding_ + 100))(), cVar1 == '\0')))) {
      pGVar2 = (GameObject *)0x0;
    }
  }
  return pGVar2;
}
