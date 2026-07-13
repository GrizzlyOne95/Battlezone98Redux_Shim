/*
 * Entry: 0047b8d2
 * Name: Apply_Free_Eye_View
 * Namespace: Global
 * Signature: void Apply_Free_Eye_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_Free_Eye_View(tagENTITY *param_1)

{
  CAMERA *pCVar1;
  QUAT *pQVar2;
  int iVar3;
  MAT_3D *pMVar4;
  MAT_3D *pMVar5;
  CAMERA *pCVar6;
  CAMERA *__return_storage_ptr__;
  CAMERA local_1ec;
  QUAT local_14;
  
  pMVar4 = &param_1->obj76->transform;
  pMVar5 = &Free_Eye_Matrix;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar5->right_x = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  Free_Eye_Sphere.origin.x = (param_1->bSphere).origin.x;
  Free_Eye_Sphere.origin.y = (param_1->bSphere).origin.y;
  Free_Eye_Sphere.origin.z = (param_1->bSphere).origin.z;
  __return_storage_ptr__ = &local_1ec;
  Free_Eye_Sphere.radius = (param_1->bSphere).radius;
  Cockpit_Visible = 0;
  useDisplayInterface = 0;
  pCVar1 = Camera_Init(__return_storage_ptr__,View_Record.MainCam.Buffer,1.3962634,
                       View_Record.MainCam.Aspect,View_Record.MainCam.Max_Depth,1.0);
  pCVar6 = &View_Record.MainCam;
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    pCVar6->Orig_x = pCVar1->Orig_x;
    pCVar1 = (CAMERA *)&pCVar1->Orig_y;
    pCVar6 = (CAMERA *)&pCVar6->Orig_y;
  }
  View_Record.Intenal_View = 0;
  View_Record.Camera_Owner = (tagENTITY *)0x0;
  View_Record.Current_View = FREE_EYE_VIEW;
  pQVar2 = Get_Matrix_Quaternion(&local_14,(MAT_3D *)__return_storage_ptr__);
  View_Record.Q.n.x = (pQVar2->n).x;
  View_Record.Q.n.y = (pQVar2->n).y;
  View_Record.Q.n.z = (pQVar2->n).z;
  View_Record.Q.w = pQVar2->w;
  View_Record.Update_Camera = Set_Free_Eye_View;
  View_Record.Q0.n.x = View_Record.Q.n.x;
  View_Record.Q0.n.y = View_Record.Q.n.y;
  View_Record.Q0.n.z = View_Record.Q.n.z;
  View_Record.Q0.w = View_Record.Q.w;
  SetControlMode(1);
  return;
}
