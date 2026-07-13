/*
 * Entry: 00493361
 * Name: std::_Unguarded_partition<GameFeature_*_*,GFPreLoadPri>
 * Namespace: std
 * Signature: pair<GameFeature_*_*,GameFeature_*_*> _Unguarded_partition<GameFeature_*_*,GFPreLoadPri>(GameFeature * * param_1, GameFeature * * param_2, GFPreLoadPri param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<GameFeature_*_*,GameFeature_*_*> __cdecl
std::_Unguarded_partition<GameFeature_*_*,GFPreLoadPri>
          (GameFeature **param_1,GameFeature **param_2,GFPreLoadPri param_3)

{
  int iVar1;
  int iVar2;
  GameFeature *extraout_EDX;
  GameFeature *pGVar3;
  GameFeature *extraout_EDX_00;
  GameFeature *extraout_EDX_01;
  GameFeature *pGVar4;
  GameFeature *pGVar5;
  GameFeature *pGVar6;
  GameFeature *pGVar7;
  pair<GameFeature_*_*,GameFeature_*_*> pVar8;
  undefined3 in_stack_0000000d;
  GFPreLoadPri in_stack_00000010;
  GameFeature *pGVar9;
  GameFeature *local_c;
  GameFeature *local_8;
  
  pGVar4 = (GameFeature *)
           (param_2 +
           (((int)_param_3 - (int)param_2 >> 2) - ((int)_param_3 - (int)param_2 >> 0x1f) >> 1));
  _Median<GameFeature_*_*,GFPreLoadPri>
            (param_2,(GameFeature **)pGVar4,(GameFeature **)&_param_3[-1].field_0x24,
             in_stack_00000010);
  pGVar3 = (GameFeature *)&pGVar4->gfName;
  while (pGVar7 = pGVar4, param_2 < pGVar7) {
    iVar1 = ((GameFeature *)pGVar7->_padding_)->preLoadPriority;
    iVar2 = *(int *)(*(int *)&pGVar7[-1].field_0x24 + 0x10);
    if ((iVar1 < iVar2) || (pGVar4 = (GameFeature *)&pGVar7[-1].field_0x24, iVar2 < iVar1)) break;
  }
  pGVar4 = pGVar3;
  local_c = pGVar7;
  local_8 = pGVar3;
  if (pGVar3 < _param_3) {
    iVar1 = ((GameFeature *)pGVar7->_padding_)->preLoadPriority;
    do {
      iVar2 = ((GameFeature *)local_8->_padding_)->preLoadPriority;
      pGVar3 = local_8;
      pGVar4 = local_8;
      if ((iVar1 < iVar2) || (iVar2 < iVar1)) break;
      pGVar3 = (GameFeature *)&local_8->gfName;
      pGVar4 = pGVar3;
      local_8 = pGVar3;
    } while (pGVar3 < _param_3);
  }
LAB_004933fd:
  do {
    pGVar6 = pGVar7;
    if (_param_3 <= pGVar4) {
joined_r0x00493407:
      while (pGVar9 = local_c, param_2 < pGVar9) {
        iVar1 = ((GameFeature *)pGVar6->_padding_)->preLoadPriority;
        local_c = (GameFeature *)&pGVar9[-1].field_0x24;
        if (*(int *)(*(int *)local_c + 0x10) <= iVar1) {
          if (*(int *)(*(int *)local_c + 0x10) < iVar1) break;
          pGVar6 = (GameFeature *)&pGVar6[-1].field_0x24;
          swap<GameFeature_*>((GameFeature **)pGVar6,(GameFeature **)local_c);
          pGVar3 = extraout_EDX_00;
        }
      }
      if (pGVar9 == (GameFeature *)param_2) {
        if (pGVar4 == _param_3) {
          *param_1 = pGVar6;
          param_1[1] = local_8;
          pVar8.second = (GameFeature **)pGVar3;
          pVar8.first = param_1;
          return pVar8;
        }
        if (local_8 != pGVar4) {
          swap<GameFeature_*>((GameFeature **)pGVar6,(GameFeature **)local_8);
        }
        pGVar7 = (GameFeature *)&pGVar6->gfName;
        pGVar5 = (GameFeature *)&pGVar4->gfName;
        pGVar3 = pGVar4;
        local_c = pGVar9;
        local_8 = (GameFeature *)&local_8->gfName;
      }
      else {
        pGVar9 = (GameFeature *)&pGVar9[-1].field_0x24;
        pGVar3 = pGVar4;
        local_c = pGVar9;
        if (pGVar4 != _param_3) goto LAB_004933f3;
        pGVar7 = (GameFeature *)&pGVar6[-1].field_0x24;
        if (pGVar9 != pGVar7) {
          swap<GameFeature_*>((GameFeature **)pGVar9,(GameFeature **)pGVar7);
        }
        pGVar3 = (GameFeature *)&local_8[-1].field_0x24;
        pGVar5 = pGVar4;
        pGVar6 = pGVar7;
        local_8 = pGVar3;
      }
      swap<GameFeature_*>((GameFeature **)pGVar6,(GameFeature **)pGVar3);
      pGVar3 = extraout_EDX_01;
      pGVar4 = pGVar5;
      goto LAB_004933fd;
    }
    iVar1 = ((GameFeature *)pGVar7->_padding_)->preLoadPriority;
    iVar2 = ((GameFeature *)pGVar4->_padding_)->preLoadPriority;
    if (iVar1 <= iVar2) {
      if (iVar1 < iVar2) goto joined_r0x00493407;
      pGVar3 = local_8;
      pGVar9 = pGVar4;
      local_8 = (GameFeature *)&local_8->gfName;
LAB_004933f3:
      swap<GameFeature_*>((GameFeature **)pGVar3,(GameFeature **)pGVar9);
      pGVar3 = extraout_EDX;
      pGVar7 = pGVar6;
    }
    pGVar4 = (GameFeature *)&pGVar4->gfName;
  } while( true );
}
