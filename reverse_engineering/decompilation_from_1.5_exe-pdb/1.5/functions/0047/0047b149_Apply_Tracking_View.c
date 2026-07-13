/*
 * Entry: 0047b149
 * Name: Apply_Tracking_View
 * Namespace: Global
 * Signature: void Apply_Tracking_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_Tracking_View(tagENTITY *param_1)

{
  CAMERA *pCVar1;
  QUAT *pQVar2;
  int iVar3;
  CAMERA *pCVar4;
  CAMERA *__return_storage_ptr__;
  CAMERA local_1ec;
  QUAT local_14;
  
  if (View_Record.Current_View == PADLOCK_VIEW) {
    Pop_Camera();
  }
  Cockpit_Visible = 0;
  __return_storage_ptr__ = &local_1ec;
  useDisplayInterface = 1;
  pCVar1 = Camera_Init(__return_storage_ptr__,View_Record.MainCam.Buffer,1.3962634,
                       View_Record.MainCam.Aspect,View_Record.MainCam.Max_Depth,1.0);
  pCVar4 = &View_Record.MainCam;
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    pCVar4->Orig_x = pCVar1->Orig_x;
    pCVar1 = (CAMERA *)&pCVar1->Orig_y;
    pCVar4 = (CAMERA *)&pCVar4->Orig_y;
  }
  View_Record.Pitch0 = View_Record.Pitch;
  View_Record.Yaw0 = View_Record.Yaw;
  View_Record.Intenal_View = 0;
  View_Record.Current_View = CHASE_VIEW;
  View_Record.Camera_Owner = param_1;
  pQVar2 = Get_Chase_Quaternion(&local_14,(tagENTITY *)__return_storage_ptr__);
  View_Record.Q.n.x = (pQVar2->n).x;
  View_Record.Q.n.y = (pQVar2->n).y;
  View_Record.Q.n.z = (pQVar2->n).z;
  View_Record.Q.w = pQVar2->w;
  View_Record.Update_Camera = Set_Chase_View;
  View_Record.Q0.n.x = View_Record.Q.n.x;
  View_Record.Q0.n.y = View_Record.Q.n.y;
  View_Record.Q0.n.z = View_Record.Q.n.z;
  View_Record.Q0.w = View_Record.Q.w;
  SetControlMode(1);
  return;
}
