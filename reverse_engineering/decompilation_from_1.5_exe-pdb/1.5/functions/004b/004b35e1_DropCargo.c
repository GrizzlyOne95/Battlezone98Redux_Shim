/*
 * Entry: 004b35e1
 * Name: DropCargo
 * Namespace: Global
 * Signature: void DropCargo(Tug * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DropCargo(Tug *param_1)

{
  GameObject *pGVar1;
  VECTOR_3D_LONG VVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  MAT_3D *pMVar5;
  Tug *unaff_EBX;
  VECTOR_3D *unaff_ESI;
  float *pfVar6;
  MAT_3D *pMVar7;
  MAT_3D local_ac;
  float local_6c [6];
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  double local_44;
  undefined8 local_3c;
  double local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  VECTOR_3D local_20;
  float local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (unaff_EBX->cargo != (GameObject *)0x0) {
    p_Var3 = (_OBJ76 *)(**(code **)(unaff_EBX->cargo->_padding_ + 0x30))();
    iVar4 = dynamic_object(p_Var3);
    if (iVar4 == 0) {
      pMVar5 = &unaff_EBX->cargo->obj->transform;
      pfVar6 = local_6c;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pfVar6 = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pfVar6 = pfVar6 + 1;
      }
      local_10 = local_54;
      local_c = local_50;
      local_8 = local_4c;
      local_2c = local_54;
      uStack_28 = local_50;
      uStack_24 = local_4c;
      VVar2.y = (double)local_3c;
      VVar2.x = local_44;
      VVar2.z._0_4_ = SUB84(local_34,0);
      VVar2.z._4_4_ = (int)((ulonglong)local_34 >> 0x20);
      Floor_GetFloor(VVar2,&local_14,&local_20);
      pMVar5 = Build_Orthogonal_Matrix
                         ((MAT_3D *)&stack0xffffff14,(VECTOR_3D *)&stack0xffffff14,unaff_ESI);
      pMVar7 = &local_ac;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        pMVar7->right_x = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      local_ac.posit_x = local_44;
      local_ac.posit_y = (double)local_14;
      local_ac.posit_z = local_34;
      GameObject::SetTransform(unaff_EBX->cargo,&local_ac);
      pGVar1 = unaff_EBX->cargo;
      (pGVar1->euler).v.x = 0.0;
      (pGVar1->euler).v_mag = 0.0;
      (pGVar1->euler).v.y = 0.0;
      (pGVar1->euler).v_mag_inv = 1e+30;
      (pGVar1->euler).v.z = 0.0;
      (pGVar1->euler).omega.x = 0.0;
      (pGVar1->euler).omega.y = 0.0;
      (pGVar1->euler).omega.z = 0.0;
      (pGVar1->euler).Accel.x = 0.0;
      (pGVar1->euler).Accel.y = 0.0;
      (pGVar1->euler).Accel.z = 0.0;
      local_10 = 0;
      local_c = 0;
      local_8 = 0;
      (pGVar1->euler).Alpha.x = 0.0;
      (pGVar1->euler).Alpha.y = 0.0;
      (pGVar1->euler).Alpha.z = 0.0;
    }
  }
  Tug::SetCargo(unaff_EBX,(GameObject *)0x0);
  return;
}
