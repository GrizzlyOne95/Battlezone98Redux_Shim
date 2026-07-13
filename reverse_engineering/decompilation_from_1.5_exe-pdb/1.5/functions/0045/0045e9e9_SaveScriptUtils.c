/*
 * Entry: 0045e9e9
 * Name: SaveScriptUtils
 * Namespace: Global
 * Signature: bool SaveScriptUtils(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl SaveScriptUtils(_iobuf *param_1)

{
  bool bVar1;
  int *piVar2;
  _loaded_aip *p_Var3;
  uint uVar4;
  char *pcVar5;
  int local_c;
  int local_8;
  
  if (missionSave) {
    bVar1 = true;
  }
  else {
    SaveAudioMessage(param_1);
    quakeMag = earthQuake.scale;
    local_c = 0;
    piVar2 = current_aip;
    do {
      if (-1 < *piVar2) {
        local_c = local_c + 1;
      }
      piVar2 = piVar2 + 1;
    } while ((int)piVar2 < 0xa0eac0);
    bVar1 = out(param_1,&local_c,4,"aip_team_count");
    local_8 = 0;
    do {
      if (-1 < current_aip[local_8]) {
        if ((bVar1 != false) && (bVar1 = out(param_1,&local_8,4,"aip_team"), bVar1)) {
          pcVar5 = "aip_name";
          uVar4 = 0xe;
          p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,current_aip[local_8]);
          bVar1 = out(param_1,p_Var3->name,uVar4,pcVar5);
          if (bVar1) {
            bVar1 = true;
            goto LAB_0045eaa4;
          }
        }
        bVar1 = false;
      }
LAB_0045eaa4:
      local_8 = local_8 + 1;
    } while (local_8 < 0x10);
    if (((((bVar1 == false) ||
          (bVar1 = out(param_1,&difficultySetting,4,"difficultySetting"), !bVar1)) ||
         (bVar1 = out(param_1,&cameraReady,1,"cameraReady"), !bVar1)) ||
        ((bVar1 = out(param_1,&cameraCallCount,4,"cameraCallCount"), !bVar1 ||
         (bVar1 = out(param_1,&quakeMag,4,"quakeMag"), !bVar1)))) ||
       ((bVar1 = CockpitTimer::Save(&cockpitTimer,param_1), !bVar1 ||
        ((bVar1 = InfoDisplay::Save(&infoDisplay,param_1), !bVar1 ||
         (bVar1 = ControlPanel::Save(&controlPanel,param_1), !bVar1)))))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  }
  return bVar1;
}
