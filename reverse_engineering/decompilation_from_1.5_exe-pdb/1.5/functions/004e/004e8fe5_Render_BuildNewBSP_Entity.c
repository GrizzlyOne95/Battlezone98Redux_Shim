/*
 * Entry: 004e8fe5
 * Name: Render_BuildNewBSP_Entity
 * Namespace: Global
 * Signature: void Render_BuildNewBSP_Entity(SORTING_LIST_ENTITY * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_BuildNewBSP_Entity(SORTING_LIST_ENTITY *param_1,CAMERA *param_2)

{
  MAT_3D *pMVar1;
  _OBJ76 *p_Var2;
  void *pvVar3;
  float fVar4;
  BSP_POLYGON *pBVar5;
  BSP_POLYGON *extraout_EDX;
  BSP_POLYGON *pBVar6;
  long unaff_EBX;
  BSP_POLYGON *unaff_ESI;
  tagENTITY *ptVar7;
  
  ptVar7 = param_1->Entity;
  if (param_1->Obj->child == (_OBJ76 *)0x0) {
    return;
  }
  Project_Polygon_Only = param_1->Project_Polygons_Flag;
  LODInfo.flags = param_1->lodFlags;
  Root_Polygon = (BSP_POLYGON *)0x0;
  Vertex_Table = Vertex_Pool;
  Local_Camera = param_2;
  Poly_Leading_Ptr = Quadtree_Cell_Pool;
  if ((char)LODInfo.flags < '\0') {
    LOD = 1;
  }
  else {
    LOD = LODInfo.flags >> 3 & 2;
  }
  param_1 = (SORTING_LIST_ENTITY *)ptVar7;
  if (ptVar7 != (tagENTITY *)0x0) {
    do {
      p_Var2 = ptVar7->obj76;
      Project_Polygon_Only = 0;
      if ((ptVar7->lodFlags & 0x20) == 0) {
        Render_Shadow(ptVar7,param_2);
      }
      pMVar1 = &p_Var2->transform;
      Submit_Sorting_Planes((_OBJ76 *)pMVar1,(MAT_3D *)unaff_ESI,unaff_EBX);
      p_Var2 = p_Var2->child;
      if (p_Var2 != (_OBJ76 *)0x0) {
        Recursive_Build_Display_List(p_Var2,pMVar1);
      }
      pBVar6 = Poly_Leading_Ptr;
      for (pvVar3 = ptVar7->mergePoly; pvVar3 != (void *)0x0;
          pvVar3 = *(void **)((int)pvVar3 + 0x14)) {
        fVar4 = *(float *)((int)pvVar3 + 0x1c) - *(float *)((int)pvVar3 + 0x28);
        if ((((fVar4 < param_2->Left != (fVar4 == param_2->Left)) ||
             (fVar4 = *(float *)((int)pvVar3 + 0x20) - *(float *)((int)pvVar3 + 0x2c),
             fVar4 < param_2->Bottom != (fVar4 == param_2->Bottom))) ||
            (param_2->Right <= *(float *)((int)pvVar3 + 0x1c) + *(float *)((int)pvVar3 + 0x28))) ||
           (param_2->Top <= *(float *)((int)pvVar3 + 0x2c) + *(float *)((int)pvVar3 + 0x20))) {
          Project_Polygon_Only = 0;
        }
        pBVar6->Texture_name[0xc] = '\0';
        pBVar6->Texture_name[0xd] = '\0';
        pBVar6->Texture_name[0xe] = '\0';
        pBVar6->Texture_name[0xf] = '\0';
        pBVar6->Color_Index = 0;
        pBVar6->Bitmap_Operation = -0x40800000;
        (pBVar6->Test).x = -*(float *)((int)pvVar3 + 0x3c);
        *(undefined4 *)pBVar6->Texture_name = *(undefined4 *)((int)pvVar3 + 0x34);
        *(undefined4 *)(pBVar6->Texture_name + 4) = *(undefined4 *)((int)pvVar3 + 0x38);
        *(undefined4 *)(pBVar6->Texture_name + 8) = *(undefined4 *)((int)pvVar3 + 0x3c);
        (pBVar6->Test).y = 0.0;
        (pBVar6->Test).z = 0.0;
        *(byte *)((int)&pBVar6->Bsp_Type + 1) = 0;
        *(undefined1 *)&pBVar6->Bsp_Type = BSP_SPRITE;
        pBVar6->Count = (long)pvVar3;
        pBVar6->Obj76 = (_OBJ76 *)0x0;
        *(byte *)((int)&pBVar6->Bsp_Type + 2) = 0;
        *(byte *)((int)&pBVar6->Bsp_Type + 3) = 0;
        pBVar5 = pBVar6;
        if (Root_Polygon != (BSP_POLYGON *)0x0) {
          Polygon_To_Poly_List(unaff_ESI);
          pBVar6 = extraout_EDX;
          pBVar5 = Root_Polygon;
        }
        Root_Polygon = pBVar5;
        pBVar6 = (BSP_POLYGON *)&pBVar6->Plane;
      }
      ptVar7 = ptVar7->mergeNext;
      Poly_Leading_Ptr = pBVar6;
    } while (ptVar7 != (tagENTITY *)0x0);
    param_1 = (SORTING_LIST_ENTITY *)0x0;
  }
  Render_Bsp_Mesh((BSP_POLYGON *)param_1);
  return;
}
