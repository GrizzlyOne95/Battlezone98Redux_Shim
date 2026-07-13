/*
 * Entry: 004f8b1e
 * Name: Get_Visible_Lights
 * Namespace: Global
 * Signature: void Get_Visible_Lights(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Get_Visible_Lights(CAMERA *param_1)

{
  MAT_3D *pMVar1;
  VECTOR_3D_LONG *pVVar2;
  VECTOR_3D *pVVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  MAT_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  float *pfVar7;
  float fVar8;
  MAT_3D local_fc;
  float local_bc [16];
  VECTOR_3D_LONG local_7c;
  VECTOR_3D local_64;
  VECTOR_3D local_58;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  double local_34;
  double local_2c;
  double local_24;
  _OBJ76 *local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  long local_8;
  
  if (TOD_tbl[Lights_Struct.TOD_entry].Day_Time != 1) {
    local_8 = 0;
    local_c = 0;
    iVar6 = 0xc16964;
    do {
      if (Lights_Struct.Light_Counter <= local_c) break;
      if ((*(byte *)(iVar6 + -0x1c) & 8) != 0) {
        local_1c = *(_OBJ76 **)(iVar6 + -0x20);
        pMVar1 = obj_rel_parent_matrix(&local_fc,local_1c,(_OBJ76 *)0x0);
        pfVar7 = local_bc;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar7 = pMVar1->right_x;
          pMVar1 = (MAT_3D *)&pMVar1->right_y;
          pfVar7 = pfVar7 + 1;
        }
        pVVar2 = Long_Vector_Transform(&local_7c,unaff_EDI,unaff_ESI);
        local_34 = pVVar2->x;
        local_2c = pVVar2->y;
        local_24 = pVVar2->z;
        pVVar3 = Camera_World_to_Camera(&local_4c,param_1,local_34,local_2c,local_24);
        local_40.x = pVVar3->x;
        local_40.y = pVVar3->y;
        local_40.z = pVVar3->z;
        lVar4 = Camera_Bounding_Sphere_Test(param_1,&local_40,*(float *)(iVar6 + -0x10) * 3.0);
        if (lVar4 < 1) {
          local_18 = (float)local_34;
          local_14 = (float)local_2c;
          Lights_Struct.Visibles_Lights[local_8] = (DYNAMIC_LIGHT *)(iVar6 + -0x20);
          local_10 = (float)local_24;
          *(float *)(iVar6 + 0x34) = local_18;
          *(float *)(iVar6 + 0x38) = local_14;
          *(float *)(iVar6 + 0x3c) = local_10;
          *(float *)(iVar6 + 0x28) = local_40.x;
          *(float *)(iVar6 + 0x2c) = local_40.y;
          *(float *)(iVar6 + 0x30) = local_40.z;
          local_8 = local_8 + 1;
          pVVar3 = Vector_Rotate(&local_64,(VECTOR_3D *)(iVar6 + -0xc),&local_1c->transform);
          ((VECTOR_3D *)(iVar6 + 0x10))->x = pVVar3->x;
          *(float *)(iVar6 + 0x14) = pVVar3->y;
          *(float *)(iVar6 + 0x18) = pVVar3->z;
          pVVar3 = Vector_Rotate(&local_58,(VECTOR_3D *)(iVar6 + 0x10),&param_1->Matrix);
          *(float *)(iVar6 + 0x1c) = pVVar3->x;
          *(float *)(iVar6 + 0x20) = pVVar3->y;
          *(float *)(iVar6 + 0x24) = pVVar3->z;
          *(undefined4 *)(iVar6 + 0xc) = 0;
          *(float *)(iVar6 + 0x40) = local_18;
          *(float *)(iVar6 + 0x44) = local_14;
          *(float *)(iVar6 + 0x48) = local_10;
          fVar8 = Terrain_FindFloor((double)local_18,(double)local_10);
          if (local_14 - fVar8 < 25.0) {
            *(float *)(iVar6 + 0x44) = *(float *)(iVar6 + 0x44) + 25.0;
            *(float *)(iVar6 + 0xc) = *(float *)(iVar6 + 0xc) - 25.0;
          }
        }
      }
      local_c = local_c + 1;
      iVar6 = iVar6 + 0x6c;
    } while (local_8 < 0x18);
    Lights_Struct.Visibles_Light_Counter = local_8;
  }
  return;
}
