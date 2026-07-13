/*
 * Entry: 0047b4e7
 * Name: Set_Free_Eye_View
 * Namespace: Global
 * Signature: void Set_Free_Eye_View(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Free_Eye_View(void)

{
  MAT_3D *pMVar1;
  MAT_3D *pMVar2;
  QUAT *pQVar3;
  int iVar4;
  QUAT *unaff_EDI;
  MAT_3D *pMVar5;
  SINCOS SVar6;
  float fVar7;
  MAT_3D local_f4;
  QUAT local_b4;
  MAT_3D local_a4;
  MAT_3D local_64;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  SINCOS local_10;
  float local_8;
  
  local_8 = TimeStepLocal();
  View_Record.Pitch = (float)eye_controls.track_pitch * local_8 + View_Record.Pitch;
  if (View_Record.Pitch < 0.017453292) {
    View_Record.Pitch = 0.017453292;
  }
  if (1.5707963 < View_Record.Pitch) {
    View_Record.Pitch = 1.5707963;
  }
  View_Record.Yaw = (float)eye_controls.track_yaw * local_8 + View_Record.Yaw;
  if (View_Record.Yaw <= 3.1415927) {
    if (View_Record.Yaw < -3.1415927) {
      View_Record.Yaw = View_Record.Yaw + 6.2831855;
      View_Record.Yaw0 = View_Record.Yaw0 + 6.2831855;
    }
  }
  else {
    View_Record.Yaw = View_Record.Yaw - 6.2831855;
    View_Record.Yaw0 = View_Record.Yaw0 - 6.2831855;
  }
  if (eye_controls.zoom_factor_reset == '\0') {
    if (eye_controls.zoom_factor_minus == '\0') {
      if (eye_controls.zoom_factor_plus == '\0') goto LAB_0047b634;
      fVar7 = TimeStep();
      View_Record.Dist = View_Record.Dist - fVar7 * View_Record.Dist * 0.5;
      fVar7 = 1.0;
      if (1.0 <= View_Record.Dist) goto LAB_0047b634;
    }
    else {
      fVar7 = TimeStep();
      View_Record.Dist = (fVar7 * 0.5 + 1.0) * View_Record.Dist;
      fVar7 = 10.0;
      if (View_Record.Dist <= 10.0) goto LAB_0047b634;
    }
  }
  else {
    fVar7 = 5.5;
  }
  View_Record.Dist = fVar7;
LAB_0047b634:
  local_8 = local_8 + local_8;
  View_Record.Dist0 = lpfilter(View_Record.Dist0,View_Record.Dist,local_8);
  View_Record.Pitch0 = lpfilter(View_Record.Pitch0,View_Record.Pitch,local_8);
  View_Record.Yaw0 = lpfilter(View_Record.Yaw0,View_Record.Yaw,local_8);
  fVar7 = Free_Eye_Sphere.radius * View_Record.Dist0;
  pMVar1 = &Identity_Matrix;
  pMVar2 = &local_a4;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar2->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  if (150.0 < fVar7) {
    fVar7 = 150.0;
  }
  local_a4.posit_z = (double)-fVar7;
  pMVar1 = &Identity_Matrix;
  pMVar2 = &local_64;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar2->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  local_10 = SinCos(View_Record.Pitch0);
  local_64.up_z = local_10.Sin;
  local_64.up_y = local_10.Cos;
  local_64.front_y = -local_64.up_z;
  local_64.front_z = local_64.up_y;
  pMVar1 = Matrix_Multiply(&local_f4,&local_a4,&local_64);
  pMVar2 = &local_a4;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar2->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  pMVar1 = &Identity_Matrix;
  pMVar2 = &local_64;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar2->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  SVar6 = SinCos(View_Record.Yaw0);
  local_64.right_x = local_10.Cos;
  local_10.Cos = SVar6.Cos;
  local_64.front_z = local_10.Cos;
  local_10.Sin = SVar6.Sin;
  local_64.right_z = local_10.Sin;
  pMVar1 = &local_f4;
  local_64.front_x = -local_10.Sin;
  local_10 = SVar6;
  pMVar2 = Matrix_Multiply(pMVar1,&local_a4,&local_64);
  pMVar5 = &local_a4;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  pQVar3 = Get_Matrix_Quaternion(&local_b4,pMVar1);
  local_18 = (pQVar3->n).x;
  local_14 = (pQVar3->n).y;
  local_10.Sin = (pQVar3->n).z;
  local_10.Cos = pQVar3->w;
  if (View_Record.Q.w * local_10.Cos +
      View_Record.Q.n.x * local_18 + local_14 * View_Record.Q.n.y + local_10.Sin * View_Record.Q.n.z
      < 0.0) {
    local_10.Cos = -local_10.Cos;
    local_18 = -local_18;
    local_14 = -local_14;
    local_10.Sin = -local_10.Sin;
  }
  View_Record.Q.n.x = local_18;
  View_Record.Q.n.y = local_14;
  View_Record.Q.n.z = local_10.Sin;
  View_Record.Q.w = local_10.Cos;
  pQVar3 = Slerp(&local_b4,&View_Record.Q0,&View_Record.Q,local_8);
  View_Record.Q0.n.x = (pQVar3->n).x;
  View_Record.Q0.n.y = (pQVar3->n).y;
  View_Record.Q0.n.z = (pQVar3->n).z;
  View_Record.Q0.w = pQVar3->w;
  pMVar1 = Quaternion_to_Matrix(&local_f4,unaff_EDI);
  pMVar2 = &local_64;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar2->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  Vector_Transform(&local_24,&Free_Eye_Sphere.origin,1,&Free_Eye_Matrix);
  local_64.posit_x = (double)local_24.x;
  local_64.posit_y = (double)local_24.y;
  local_64.posit_z = (double)local_24.z;
  pMVar1 = Matrix_Multiply(&local_f4,&local_a4,&local_64);
  pMVar2 = &local_a4;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar2->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  fVar7 = Terrain_FindFloor(local_a4.posit_x,local_a4.posit_z);
  if ((float)local_a4.posit_y < fVar7 + 0.5) {
    local_a4.posit_y = (double)(fVar7 + 0.5);
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_a4);
  return;
}
