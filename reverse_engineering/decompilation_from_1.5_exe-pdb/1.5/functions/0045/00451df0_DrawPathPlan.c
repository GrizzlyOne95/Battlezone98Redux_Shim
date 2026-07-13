/*
 * Entry: 00451df0
 * Name: DrawPathPlan
 * Namespace: Global
 * Signature: void DrawPathPlan(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DrawPathPlan(float param_1,float param_2)

{
  int *piVar1;
  Strip **ppSVar2;
  Strip *pSVar3;
  float fVar4;
  float fVar5;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar6;
  int iVar7;
  Strip *pSVar8;
  Strip **ppSVar9;
  Strip ***pppSVar10;
  float local_94;
  vector<Strip_*,std::allocator<Strip_*>_> *local_90;
  Strip ***local_8c;
  Strip ***local_88;
  char local_84 [128];
  uint local_4;
  
  pvVar6 = usedStrips;
  local_4 = __security_cookie ^ (uint)&local_94;
  if ((curFindPath != (PathPlan *)0x0) && ((curFindPath->flags & 4) != 0)) {
    local_94 = 25.0;
    ppSVar9 = usedStrips->_Myfirst;
    local_88 = &usedStrips->_Myfirst;
    pppSVar10 = &usedStrips->_Mylast;
    pSVar8 = (Strip *)0x0;
    local_90 = usedStrips;
    local_8c = pppSVar10;
    if (*pppSVar10 < ppSVar9) {
      _invalid_parameter_noinfo();
    }
    piVar1 = (int *)pvVar6->_padding_;
    while( true ) {
      ppSVar2 = *pppSVar10;
      if (ppSVar2 < *local_88) {
        _invalid_parameter_noinfo();
      }
      if ((piVar1 == (int *)0x0) || (piVar1 != (int *)local_90->_padding_)) {
        _invalid_parameter_noinfo();
      }
      if (ppSVar9 == ppSVar2) break;
      if (piVar1 == (int *)0x0) {
        _invalid_parameter_noinfo();
        iVar7 = 0;
      }
      else {
        iVar7 = *piVar1;
      }
      if (*(Strip ***)(iVar7 + 0x10) <= ppSVar9) {
        _invalid_parameter_noinfo();
      }
      pSVar3 = *ppSVar9;
      fVar4 = pSVar3->x * Terrain.Grid_Size - param_1;
      fVar5 = Terrain.Grid_Size * pSVar3->z - param_2;
      fVar4 = fVar5 * fVar5 + fVar4 * fVar4;
      if (fVar4 < local_94) {
        pSVar8 = pSVar3;
        local_94 = fVar4;
      }
      if (piVar1 == (int *)0x0) {
        _invalid_parameter_noinfo();
        iVar7 = 0;
      }
      else {
        iVar7 = *piVar1;
      }
      if (*(Strip ***)(iVar7 + 0x10) <= ppSVar9) {
        _invalid_parameter_noinfo();
      }
      ppSVar9 = ppSVar9 + 1;
      pppSVar10 = local_8c;
    }
    if (pSVar8 != (Strip *)0x0) {
      sprintf_s<128>(&local_84,"x(%0.2f) z(%0.2f) g(%0.2f) h(%0.2f) cost(%0.2f) forward(%d)");
    }
  }
  return;
}
