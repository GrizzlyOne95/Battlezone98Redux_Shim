/*
 * Entry: 0047a8d0
 * Name: Apply_Cockpit_View
 * Namespace: Global
 * Signature: void Apply_Cockpit_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_Cockpit_View(tagENTITY *param_1)

{
  CAMERA *pCVar1;
  QUAT *pQVar2;
  int iVar3;
  MAT_3D *unaff_EDI;
  CAMERA *pCVar4;
  CAMERA local_1ec;
  QUAT local_14;
  
  if (View_Record.Current_View == PADLOCK_VIEW) {
    Pop_Camera();
  }
  Cockpit_Visible = 1;
  useDisplayInterface = 1;
  pCVar1 = Camera_Init(&local_1ec,View_Record.MainCam.Buffer,1.3962634,View_Record.MainCam.Aspect,
                       View_Record.MainCam.Max_Depth,cockpit_zoom);
  pCVar4 = &View_Record.MainCam;
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    pCVar4->Orig_x = pCVar1->Orig_x;
    pCVar1 = (CAMERA *)&pCVar1->Orig_y;
    pCVar4 = (CAMERA *)&pCVar4->Orig_y;
  }
  pQVar2 = Matrix_to_Quaternion(&local_14,unaff_EDI);
  View_Record.Q.n.x = (pQVar2->n).x;
  View_Record.Q.n.y = (pQVar2->n).y;
  View_Record.Q.n.z = (pQVar2->n).z;
  View_Record.Q.w = pQVar2->w;
  View_Record.Current_View = COCKPIT_VIEW;
  View_Record.Intenal_View = 1;
  View_Record.Camera_Owner = param_1;
  View_Record.Update_Camera = Set_Cockpit_View;
  View_Record.Q0.n.x = View_Record.Q.n.x;
  View_Record.Q0.n.y = View_Record.Q.n.y;
  View_Record.Q0.n.z = View_Record.Q.n.z;
  View_Record.Q0.w = View_Record.Q.w;
  SetControlMode(1);
  return;
}
