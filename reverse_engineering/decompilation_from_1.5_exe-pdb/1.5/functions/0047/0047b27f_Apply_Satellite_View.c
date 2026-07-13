/*
 * Entry: 0047b27f
 * Name: Apply_Satellite_View
 * Namespace: Global
 * Signature: void Apply_Satellite_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_Satellite_View(tagENTITY *param_1)

{
  int iVar1;
  CAMERA *pCVar2;
  CAMERA *pCVar3;
  float fVar4;
  CAMERA local_1dc;
  
  iVar1 = ControlPanel_SatelliteEnabled();
  if (iVar1 != 0) {
    if (View_Record.Current_View == PADLOCK_VIEW) {
      Pop_Camera();
    }
    Cockpit_Visible = 0;
    useDisplayInterface = 1;
    OverView_SetObject(param_1->obj76);
    fVar4 = OverView_GetZoom();
    pCVar2 = Camera_Init(&local_1dc,View_Record.MainCam.Buffer,1.5707963,View_Record.MainCam.Aspect,
                         1000.0,fVar4);
    pCVar3 = &View_Record.MainCam;
    for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
      pCVar3->Orig_x = pCVar2->Orig_x;
      pCVar2 = (CAMERA *)&pCVar2->Orig_y;
      pCVar3 = (CAMERA *)&pCVar3->Orig_y;
    }
    View_Record.Intenal_View = 0;
    View_Record.Current_View = OVER_VIEW;
    View_Record.Camera_Owner = param_1;
    View_Record.Update_Camera = Set_Satellite_View;
    SetControlMode(0);
  }
  return;
}
