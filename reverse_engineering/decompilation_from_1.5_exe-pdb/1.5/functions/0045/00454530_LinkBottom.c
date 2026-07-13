/*
 * Entry: 00454530
 * Name: LinkBottom
 * Namespace: Global
 * Signature: void LinkBottom(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LinkBottom(Strip *param_1)

{
  int iVar1;
  Strip *pSVar2;
  PathZone *pPVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  pPVar3 = GetZone(param_1->x0,param_1->z1 + 0.1);
  if (pPVar3 != (PathZone *)0x0) {
    floor((double)param_1->x0);
    _ftol2_sse();
    iVar5 = extraout_EAX - pPVar3->x0;
    floor((double)param_1->x1);
    _ftol2_sse();
    iVar4 = extraout_EAX_00 - pPVar3->x0;
    floor((double)param_1->z1);
    _ftol2_sse();
    iVar1 = pPVar3->z0;
    if (iVar5 < iVar4) {
      do {
        uVar6 = (uint)*(byte *)((int)pPVar3 + iVar5 + (extraout_EAX_01 - iVar1) * 0x10 + 0x24);
        if ((uint)((int)(pPVar3->terrainStrips)._Mylast - (int)(pPVar3->terrainStrips)._Myfirst >> 2
                  ) <= uVar6) {
          _invalid_parameter_noinfo();
        }
        pSVar2 = (pPVar3->terrainStrips)._Myfirst[uVar6];
        floor((double)pSVar2->x1);
        _ftol2_sse();
        iVar5 = extraout_EAX_02 - pPVar3->x0;
        if ((pSVar2->material != 6) && (pSVar2->material != 5)) {
          ContainerNeighbor::Link(param_1,pSVar2);
        }
      } while (iVar5 < iVar4);
    }
  }
  return;
}
