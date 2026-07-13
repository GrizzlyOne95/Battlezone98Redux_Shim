/*
 * Entry: 0047b3a9
 * Name: Apply_Edit_View
 * Namespace: Global
 * Signature: void Apply_Edit_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_Edit_View(tagENTITY *param_1)

{
  _OBJ76 *p_Var1;
  CAMERA *pCVar2;
  int iVar3;
  tagENTITY *unaff_EBX;
  CAMERA *pCVar4;
  float fVar5;
  CAMERA local_1e8;
  VECTOR_3D local_10;
  
  if (View_Record.Current_View == PADLOCK_VIEW) {
    Pop_Camera();
  }
  Cockpit_Visible = 0;
  useDisplayInterface = 1;
  fVar5 = EditTerrain_GetZoom();
  pCVar2 = Camera_Init(&local_1e8,View_Record.MainCam.Buffer,1.5707963,View_Record.MainCam.Aspect,
                       1000.0,fVar5);
  pCVar4 = &View_Record.MainCam;
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    pCVar4->Orig_x = pCVar2->Orig_x;
    pCVar2 = (CAMERA *)&pCVar2->Orig_y;
    pCVar4 = (CAMERA *)&pCVar4->Orig_y;
  }
  p_Var1 = unaff_EBX->obj76;
  local_10.x = (float)(p_Var1->transform).posit_x;
  local_10.y = (float)(p_Var1->transform).posit_y;
  local_10.z = (float)(p_Var1->transform).posit_z;
  EditTerrain_SetTarget(&local_10);
  View_Record.Intenal_View = 0;
  View_Record.Current_View = EDIT_VIEW;
  View_Record.Update_Camera = Set_Edit_View;
  View_Record.Camera_Owner = unaff_EBX;
  SetControlMode(0);
  EditTerrain_Enter();
  return;
}
