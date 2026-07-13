/*
 * Entry: 004e80f1
 * Name: Cache_Make_Poly
 * Namespace: Global
 * Signature: void * Cache_Make_Poly(_OBJ76 * param_1, FACE * param_2, MAT_3D * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Cache_Make_Poly(_OBJ76 *param_1,FACE *param_2,MAT_3D *param_3,long param_4)

{
  long *plVar1;
  byte bVar2;
  PLANE *pPVar3;
  float *pfVar4;
  BSP_POLYGON *pBVar5;
  COLOR *pCVar6;
  int iVar7;
  PLANE local_14;
  
  if (0x1000 < ((param_2->vertex_count + 2) * 0x18 - Poly_Base_Ptr) + (int)Poly_Leading_Ptr) {
    Add_Container(Current_Entity);
  }
  pBVar5 = Poly_Leading_Ptr;
  (Poly_Leading_Ptr->Test).y = 0.0;
  (pBVar5->Test).z = 0.0;
  *(byte *)((int)&pBVar5->Bsp_Type + 1) = 0;
  *(undefined1 *)&pBVar5->Bsp_Type = BSP_SINGLE_POLYGON;
  if (param_2->vertex_count < 3) {
    pBVar5->Texture_name[0] = '\0';
    pBVar5->Texture_name[1] = '\0';
    pBVar5->Texture_name[2] = '\0';
    pBVar5->Texture_name[3] = '\0';
    pBVar5->Texture_name[4] = '\0';
    pBVar5->Texture_name[5] = '\0';
    pBVar5->Texture_name[6] = '\0';
    pBVar5->Texture_name[7] = '\0';
    pBVar5->Texture_name[8] = '\0';
    pBVar5->Texture_name[9] = '\0';
    pBVar5->Texture_name[10] = '\0';
    pBVar5->Texture_name[0xb] = '\0';
    pBVar5->Texture_name[0xc] = '\0';
    pBVar5->Texture_name[0xd] = '\0';
    pBVar5->Texture_name[0xe] = '\0';
    pBVar5->Texture_name[0xf] = '\0';
    pBVar5->Color_Index = 0;
    pBVar5->Bitmap_Operation = 0;
    (pBVar5->Test).x = 0.0;
  }
  else {
    Vector_Transform((VECTOR_3D *)pBVar5->Texture_name,&param_2->Test_Point,1,param_3);
    pPVar3 = Plane_Transform(&local_14,&param_2->plane,param_3);
    pBVar5 = Poly_Leading_Ptr;
    plVar1 = &Poly_Leading_Ptr->Color_Index;
    *(float *)(Poly_Leading_Ptr->Texture_name + 0xc) = (pPVar3->surf_normal).x;
    *plVar1 = (long)(pPVar3->surf_normal).y;
    pBVar5->Bitmap_Operation = (long)(pPVar3->surf_normal).z;
    (pBVar5->Test).x = pPVar3->dist;
  }
  pBVar5->Count = (long)param_1;
  pBVar5->Obj76 =
       (_OBJ76 *)(-(uint)(param_2->texture_name[0] != '\0') & (uint)param_2->texture_name);
  *(uchar *)((int)&pBVar5->Bsp_Type + 2) = (param_2->color).index;
  if (param_2->ShadeType == '\0') {
    param_2->ShadeType = '\x04';
  }
  bVar2 = sniped_by[((uint)param_2->TextureType + (uint)param_2->ShadeType * 8) * 4 + 0xf8];
  *(byte *)((int)&pBVar5->Bsp_Type + 3) = bVar2;
  if (param_2->XluscentType != '\0') {
    *(byte *)((int)&pBVar5->Bsp_Type + 3) = bVar2 | 0x80;
  }
  *(byte *)((int)&pBVar5->Bsp_Type + 1) = (byte)param_2->vertex_count;
  iVar7 = 0;
  if (0 < param_2->vertex_count) {
    pfVar4 = (float *)&param_2[1].vertex_count;
    pCVar6 = (COLOR *)&(pBVar5->Plane).surf_normal.z;
    do {
      ((VECTOR_3D *)(pCVar6 + -2))->x = (float)(((FACE *)(pfVar4 + -1))->index + param_4);
      iVar7 = iVar7 + 1;
      pCVar6[-1] = (COLOR)((int)*pfVar4 + param_4);
      *pCVar6 = *(COLOR *)(pfVar4 + 1);
      pCVar6[1] = *(COLOR *)(pfVar4 + 2);
      pfVar4 = pfVar4 + 4;
      pCVar6 = pCVar6 + 4;
    } while (iVar7 < param_2->vertex_count);
  }
  return pBVar5->Texture_name + param_2->vertex_count * 0x10 + 0x24;
}
