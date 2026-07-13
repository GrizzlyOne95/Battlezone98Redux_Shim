/*
 * Entry: 0047834d
 * Name: RenderHUD
 * Namespace: Global
 * Signature: void RenderHUD(CAMERA * param_1, tagENTITY * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RenderHUD(CAMERA *param_1,tagENTITY *param_2,int param_3)

{
  int iVar1;
  
  if (((Cockpit_Visible != 0) && (param_2 != (tagENTITY *)0x0)) && (param_3 != 0)) {
    Render_Entity_Cockpit(param_1,param_2);
  }
  if (useDisplayInterface != 0) {
    if (D3RadarType == 1) {
      if (hudFlags != 0) {
        Render_RadarBackdrop();
        End_D3D_Scene();
        iVar1 = (*Device.VideoMode.LockBuffer)(&Device);
        if (iVar1 != 0) {
          Render_RadarMesh();
        }
        (*Device.VideoMode.UnlockBuffer)(&Device);
        Begin_D3D_Scene(param_1);
      }
    }
    else if (hudFlags != 0) {
      Render_RadarMesh();
    }
    DisplayInterface_RenderAll();
  }
  GameFeature_RenderAll();
  Update_FPS();
  Show_framerate(&View_Record.MainCam);
  Scroll_Tick();
  TextInput_Update();
  Scores_DisplayScores();
  Network_DisplayInfo(&View_Record.MainCam);
  return;
}
