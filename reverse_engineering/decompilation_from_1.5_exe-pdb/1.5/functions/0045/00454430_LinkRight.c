/*
 * Entry: 00454430
 * Name: LinkRight
 * Namespace: Global
 * Signature: void LinkRight(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LinkRight(Strip *param_1)

{
  int iVar1;
  int iVar2;
  Strip *pSVar3;
  PathZone *pPVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar5;
  uint uVar6;
  
  pPVar4 = GetZone(param_1->x1 + 0.1,param_1->z0);
  if (pPVar4 != (PathZone *)0x0) {
    floor((double)param_1->x1);
    _ftol2_sse();
    iVar1 = pPVar4->x0;
    floor((double)param_1->z0);
    _ftol2_sse();
    iVar5 = extraout_EAX_00 - pPVar4->z0;
    floor((double)param_1->z1);
    _ftol2_sse();
    iVar2 = pPVar4->z0;
    while (iVar5 < extraout_EAX_01 - iVar2) {
      uVar6 = (uint)*(byte *)(iVar5 * 0x10 + (extraout_EAX - iVar1) + 0x24 + (int)pPVar4);
      if ((uint)((int)(pPVar4->terrainStrips)._Mylast - (int)(pPVar4->terrainStrips)._Myfirst >> 2)
          <= uVar6) {
        _invalid_parameter_noinfo();
      }
      pSVar3 = (pPVar4->terrainStrips)._Myfirst[uVar6];
      floor((double)pSVar3->z1);
      _ftol2_sse();
      iVar5 = extraout_EAX_02 - pPVar4->z0;
      if ((pSVar3->material != 6) && (pSVar3->material != 5)) {
        ContainerNeighbor::Link(param_1,pSVar3);
      }
    }
  }
  return;
}
