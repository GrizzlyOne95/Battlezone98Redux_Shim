/*
 * Entry: 0047ac8d
 * Name: Apply_Front_View
 * Namespace: Global
 * Signature: void Apply_Front_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_Front_View(tagENTITY *param_1)

{
  CAMERA *pCVar1;
  int iVar2;
  CAMERA *pCVar3;
  CAMERA local_1dc;
  
  if (View_Record.Current_View == PADLOCK_VIEW) {
    Pop_Camera();
  }
  Cockpit_Visible = 0;
  useDisplayInterface = 1;
  pCVar1 = Camera_Init(&local_1dc,View_Record.MainCam.Buffer,1.3962634,View_Record.MainCam.Aspect,
                       View_Record.MainCam.Max_Depth,1.0);
  pCVar3 = &View_Record.MainCam;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    pCVar3->Orig_x = pCVar1->Orig_x;
    pCVar1 = (CAMERA *)&pCVar1->Orig_y;
    pCVar3 = (CAMERA *)&pCVar3->Orig_y;
  }
  View_Record.Pitch0 = 0.0;
  View_Record.Yaw0 = 0.0;
  View_Record.x0 = 0.0;
  View_Record.y0 = 5.0;
  View_Record.z0 = 0.0;
  View_Record.Intenal_View = 0;
  View_Record.Current_View = FIX_EXTERN_VIEW;
  View_Record.Camera_Owner = param_1;
  View_Record.Update_Camera = Set_External_View;
  SetControlMode(1);
  return;
}
