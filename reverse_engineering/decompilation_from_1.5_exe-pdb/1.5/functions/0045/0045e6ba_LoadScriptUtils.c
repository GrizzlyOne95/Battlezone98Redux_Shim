/*
 * Entry: 0045e6ba
 * Name: LoadScriptUtils
 * Namespace: Global
 * Signature: bool LoadScriptUtils(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl LoadScriptUtils(_iobuf *param_1)

{
  byte bVar1;
  _loaded_aip *p_Var2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  int *piVar6;
  byte *pbVar7;
  bool bVar8;
  int local_2c;
  int local_28;
  int local_24;
  _iobuf *local_20;
  char local_19;
  byte local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  quakeMag = 0.0;
  piVar6 = current_aip;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = -1;
    piVar6 = piVar6 + 1;
  }
  local_20 = param_1;
  cameraReady = false;
  loadInCamera = false;
  ExpandingArray<_loaded_aip>::Clear(&loaded_aips);
  loaded_aip_count = 0;
  if (missionSave != false) {
    loaded_aip_count = 0;
    return true;
  }
  LoadAudioMessage(param_1);
  local_18[0] = 0;
  if (version < 0x411) {
    local_19 = in(param_1,(char *)local_18,0xe);
    iVar4 = 5;
    bVar8 = true;
    pbVar5 = local_18;
    pbVar7 = &s_null;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar8 = *pbVar5 == *pbVar7;
      pbVar5 = pbVar5 + 1;
      pbVar7 = pbVar7 + 1;
    } while (bVar8);
    param_1 = local_20;
    if (!bVar8) {
      pbVar5 = local_18;
      p_Var2 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,0);
      do {
        bVar1 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        p_Var2->name[0] = bVar1;
        p_Var2 = (_loaded_aip *)(p_Var2->name + 1);
      } while (bVar1 != 0);
      loaded_aip_count = loaded_aip_count + 1;
      current_aip[2] = 0;
      param_1 = local_20;
    }
  }
  else {
    local_19 = in(param_1,&local_28,4);
    local_24 = 0;
    if (0 < local_28) {
      do {
        if ((local_19 == '\0') || (bVar8 = in(param_1,&local_2c,4), !bVar8)) {
LAB_0045e823:
          local_19 = '\0';
        }
        else {
          bVar8 = in(param_1,(char *)local_18,0xe);
          local_19 = '\x01';
          if (!bVar8) goto LAB_0045e823;
        }
        iVar4 = 0;
        if (0 < loaded_aip_count) {
          do {
            p_Var2 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar4);
            pbVar5 = local_18;
            do {
              bVar1 = *pbVar5;
              bVar8 = bVar1 < (byte)p_Var2->name[0];
              if (bVar1 != p_Var2->name[0]) {
LAB_0045e85a:
                iVar3 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                goto LAB_0045e85f;
              }
              if (bVar1 == 0) break;
              bVar1 = pbVar5[1];
              bVar8 = bVar1 < (byte)p_Var2->name[1];
              if (bVar1 != p_Var2->name[1]) goto LAB_0045e85a;
              pbVar5 = pbVar5 + 2;
              p_Var2 = (_loaded_aip *)(p_Var2->name + 2);
            } while (bVar1 != 0);
            iVar3 = 0;
LAB_0045e85f:
          } while ((iVar3 != 0) && (iVar4 = iVar4 + 1, iVar4 < loaded_aip_count));
        }
        if (iVar4 == loaded_aip_count) {
          pbVar5 = local_18;
          p_Var2 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar4);
          do {
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 1;
            p_Var2->name[0] = bVar1;
            p_Var2 = (_loaded_aip *)(p_Var2->name + 1);
          } while (bVar1 != 0);
          loaded_aip_count = loaded_aip_count + 1;
          param_1 = local_20;
        }
        local_24 = local_24 + 1;
        current_aip[local_2c] = iVar4;
      } while (local_24 < local_28);
    }
  }
  if ((((local_19 == '\0') || (bVar8 = in(param_1,&difficultySetting,4), !bVar8)) ||
      (bVar8 = in(param_1,&cameraReady,1), !bVar8)) ||
     (bVar8 = in(param_1,&cameraCallCount,4), !bVar8)) {
    bVar8 = false;
  }
  else {
    bVar8 = true;
  }
  if (0x40c < version) {
    if ((bVar8) && (bVar8 = in(param_1,&quakeMag,4), bVar8)) goto LAB_0045e8dc;
    bVar8 = false;
  }
  if (!bVar8) {
    return true;
  }
LAB_0045e8dc:
  bVar8 = CockpitTimer::Load(&cockpitTimer,param_1);
  if ((bVar8) && (bVar8 = InfoDisplay::Load(&infoDisplay,param_1), bVar8)) {
    ControlPanel::Load(&controlPanel,param_1);
  }
  return true;
}
