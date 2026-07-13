/*
 * Entry: 0045e916
 * Name: PostLoadScriptUtils
 * Namespace: Global
 * Signature: bool PostLoadScriptUtils(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PostLoadScriptUtils(void)

{
  int iVar1;
  int iVar2;
  _loaded_aip *p_Var3;
  void *pvVar4;
  
  while (iVar2 = isCineractive(), iVar2 != 0) {
    Trace("fsm_pop_camera called again\n");
    fsm_pop_camera();
  }
  scriptLoadTime = Get_Time();
  if (missionSave == false) {
    iVar2 = 0;
    if (0 < loaded_aip_count) {
      do {
        p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar2);
        pvVar4 = AISchedule_LoadAIP(-1,p_Var3->name);
        p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar2);
        iVar1 = loaded_aip_count;
        iVar2 = iVar2 + 1;
        p_Var3->aip = pvVar4;
      } while (iVar2 < iVar1);
    }
    iVar2 = 0;
    do {
      if (-1 < current_aip[iVar2]) {
        p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,current_aip[iVar2]);
        AISchedule_SwitchAIP(iVar2,p_Var3->aip);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x10);
    if (cameraReady != false) {
      loadInCamera = true;
      DisableInputs();
    }
    if (quakeMag != 0.0) {
      EarthQuake::StartQuake(&earthQuake,quakeMag);
    }
  }
  return true;
}
