/*
 * Entry: 0047a998
 * Name: Set_External_View
 * Namespace: Global
 * Signature: void Set_External_View(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_External_View(void)

{
  tagENTITY *ptVar1;
  MAT_3D *pMVar2;
  QUAT *pQVar3;
  int iVar4;
  QUAT *unaff_EDI;
  MAT_3D *pMVar5;
  SINCOS SVar6;
  float fVar7;
  tagENTITY *ptVar8;
  undefined1 local_f8 [80];
  MAT_3D local_a8;
  MAT_3D local_68;
  VECTOR_3D local_28;
  tagENTITY *local_1c;
  float local_18;
  float local_14;
  float local_10;
  SINCOS local_c;
  
  local_1c = Get_Camera_Owner();
  local_18 = TimeStepLocal();
  if (eye_controls.zoom_factor_reset == '\0') {
    if (eye_controls.zoom_factor_minus == '\0') {
      if (eye_controls.zoom_factor_plus == '\0') goto LAB_0047aa37;
      fVar7 = TimeStep();
      View_Record.Dist = View_Record.Dist - fVar7 * View_Record.Dist * 0.5;
      fVar7 = 1.0;
      if (1.0 <= View_Record.Dist) goto LAB_0047aa37;
    }
    else {
      fVar7 = TimeStep();
      View_Record.Dist = (fVar7 * 0.5 + 1.0) * View_Record.Dist;
      fVar7 = 10.0;
      if (View_Record.Dist <= 10.0) goto LAB_0047aa37;
    }
  }
  else {
    fVar7 = 5.5;
  }
  View_Record.Dist = fVar7;
LAB_0047aa37:
  View_Record.Dist0 = lpfilter(View_Record.Dist0,View_Record.Dist,local_18 + local_18);
  ptVar8 = local_1c;
  pMVar2 = &Identity_Matrix;
  pMVar5 = &local_a8;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  fVar7 = View_Record.Dist0 * (ptVar8->bSphere).radius;
  if (150.0 < fVar7) {
    fVar7 = 150.0;
  }
  local_a8.posit_z = (double)-fVar7;
  pMVar2 = &Identity_Matrix;
  pMVar5 = &local_68;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  local_c = SinCos(View_Record.Pitch0);
  local_68.up_z = local_c.Sin;
  local_68.up_y = local_c.Cos;
  local_68.front_y = -local_68.up_z;
  local_68.front_z = local_68.up_y;
  pMVar2 = Matrix_Multiply((MAT_3D *)local_f8,&local_a8,&local_68);
  pMVar5 = &local_a8;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  pMVar2 = &Identity_Matrix;
  pMVar5 = &local_68;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  SVar6 = SinCos(View_Record.Yaw0);
  local_68.right_x = local_c.Cos;
  local_c.Cos = SVar6.Cos;
  local_68.front_z = local_c.Cos;
  local_c.Sin = SVar6.Sin;
  local_68.right_z = local_c.Sin;
  ptVar8 = (tagENTITY *)local_f8;
  local_68.front_x = -local_c.Sin;
  local_c = SVar6;
  pMVar2 = Matrix_Multiply((MAT_3D *)ptVar8,&local_a8,&local_68);
  ptVar1 = local_1c;
  pMVar5 = &local_a8;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  pQVar3 = Get_Chase_Quaternion((QUAT *)(local_f8 + 0x40),ptVar8);
  local_14 = (pQVar3->n).x;
  local_10 = (pQVar3->n).y;
  local_c.Sin = (pQVar3->n).z;
  local_c.Cos = pQVar3->w;
  if (View_Record.Q.w * local_c.Cos +
      View_Record.Q.n.x * local_14 + local_10 * View_Record.Q.n.y + local_c.Sin * View_Record.Q.n.z
      < 0.0) {
    local_c.Cos = -local_c.Cos;
    local_14 = -local_14;
    local_10 = -local_10;
    local_c.Sin = -local_c.Sin;
  }
  View_Record.Q.n.x = local_14;
  View_Record.Q.n.y = local_10;
  View_Record.Q.n.z = local_c.Sin;
  View_Record.Q.w = local_c.Cos;
  pQVar3 = Slerp((QUAT *)(local_f8 + 0x40),&View_Record.Q0,&View_Record.Q,local_18 * 5.0);
  View_Record.Q0.n.x = (pQVar3->n).x;
  View_Record.Q0.n.y = (pQVar3->n).y;
  View_Record.Q0.n.z = (pQVar3->n).z;
  View_Record.Q0.w = pQVar3->w;
  pMVar2 = Quaternion_to_Matrix((MAT_3D *)local_f8,unaff_EDI);
  pMVar5 = &local_68;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  Vector_Transform(&local_28,&(ptVar1->bSphere).origin,1,&ptVar1->obj76->transform);
  local_68.posit_x = (double)local_28.x;
  local_68.posit_y = (double)(local_28.y + 5.0);
  local_68.posit_z = (double)local_28.z;
  pMVar2 = Matrix_Multiply((MAT_3D *)local_f8,&local_a8,&local_68);
  pMVar5 = &local_a8;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  fVar7 = Terrain_FindFloor(local_a8.posit_x,local_a8.posit_z);
  if ((float)local_a8.posit_y < fVar7 + 0.5) {
    local_a8.posit_y = (double)(fVar7 + 0.5);
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_a8);
  return;
}
