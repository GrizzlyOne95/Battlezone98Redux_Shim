/*
 * Entry: 0047a76f
 * Name: Init_View_Record
 * Namespace: Global
 * Signature: void Init_View_Record(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_View_Record(int param_1)

{
  float fVar1;
  long lVar2;
  CAMERA *pCVar3;
  CAMERA *pCVar4;
  tagENTITY *ptVar5;
  int iVar6;
  float *pfVar7;
  float fVar8;
  float fVar9;
  CAMERA local_1dc;
  
  view_cars_only = 1;
  if ((param_1 == 1) ||
     (fVar8 = View_Record.MainCam.Max_Depth, fVar9 = View_Record.MainCam.Zoom_Factor,
     fVar1 = View_Record.MainCam.View_Angle, View_Record.MainCam.View_Angle == 0.0)) {
    fVar8 = FarClip;
    fVar9 = 1.0;
    fVar1 = 1.3962634;
  }
  pCVar3 = Camera_Init(&local_1dc,&Device.Viewport,fVar1,1.0,fVar8,fVar9);
  lVar2 = Camera_Stack_Index;
  pCVar4 = &View_Record.MainCam;
  for (iVar6 = 0x76; iVar6 != 0; iVar6 = iVar6 + -1) {
    pCVar4->Orig_x = pCVar3->Orig_x;
    pCVar3 = (CAMERA *)&pCVar3->Orig_y;
    pCVar4 = (CAMERA *)&pCVar4->Orig_y;
  }
  if (lVar2 < 8) {
    pfVar7 = &Camera_Stack[lVar2].MainCam.Max_Depth;
    do {
      pCVar4 = Camera_Init(&local_1dc,&Device.Viewport,pfVar7[5],pfVar7[7],*pfVar7,pfVar7[8]);
      pCVar3 = (CAMERA *)(pfVar7 + -4);
      pfVar7 = pfVar7 + 0x8e;
      for (iVar6 = 0x76; iVar6 != 0; iVar6 = iVar6 + -1) {
        pCVar3->Orig_x = pCVar4->Orig_x;
        pCVar4 = (CAMERA *)&pCVar4->Orig_y;
        pCVar3 = (CAMERA *)&pCVar3->Orig_y;
      }
    } while ((int)pfVar7 < 0xd42320);
  }
  if (param_1 == 1) {
    View_Record.Pitch = 0.5235988;
    View_Record.Camera_Owner = (tagENTITY *)0x0;
    View_Record.Pitch0 = 0.5235988;
    View_Record.Intenal_View = 1;
    View_Record.Current_View = COCKPIT_VIEW;
    View_Record.Yaw = 0.0;
    View_Record.Update_Camera = (_func___cdecl_void *)0x0;
    View_Record.Yaw0 = 0.0;
    View_Record.Dist = 5.5;
    View_Record.Dist0 = 5.5;
    ptVar5 = get_user_entity();
    if (ptVar5 != (tagENTITY *)0x0) {
      Set_View(ptVar5,GK_COCKPIT_VIEW);
    }
    cockpit_zoom = 1.0;
  }
  return;
}
