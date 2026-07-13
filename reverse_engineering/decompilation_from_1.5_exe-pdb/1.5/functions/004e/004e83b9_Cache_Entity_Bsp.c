/*
 * Entry: 004e83b9
 * Name: Cache_Entity_Bsp
 * Namespace: Global
 * Signature: void Cache_Entity_Bsp(tagENTITY * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Entity_Bsp(tagENTITY *param_1,long param_2)

{
  _OBJ76 *p_Var1;
  ulong uVar2;
  long lVar3;
  MATRIX_STACK *pMVar4;
  MATRIX_LIST *unaff_EBX;
  long unaff_EDI;
  MATRIX_LIST local_904 [32];
  
  uVar2 = Get_Frame_Count();
  param_1->Bsp_LRU_Stamp = uVar2;
  if (param_1->Bsp_Geom_LOD != param_2) {
    if (param_1->Bsp_Container != (BSP_CONTAINER *)0x0) {
      Delete_Container(param_1);
    }
    Add_Container(param_1);
    lVar3 = Active_Entity_Counter;
    Active_Entity_Counter = Active_Entity_Counter + 1;
    Active_Entity_Heap[lVar3] = param_1;
    Root_Polygon = (BSP_POLYGON *)0x0;
    Entity_Vertex_Count = 0;
    Moving_Objects_Counter = 0;
    p_Var1 = param_1->obj76;
    Bsp_Moving_Objects = local_904;
    param_1->Bsp_Geom_LOD = param_2;
    Current_Entity = param_1;
    LOD = param_2;
    Bsp_Backbone = (MATRIX_LIST *)Vertex_Pool;
    lVar3 = Cache_Build_Bsp_Backbone(p_Var1->child,&Identity_Matrix,0);
    pMVar4 = Cache_Sort_Bsp_Backbone(unaff_EBX,unaff_EDI);
    param_1->Bsp_Vertex_Pool_Size = Entity_Vertex_Count;
    if (param_2 != 4) {
      Cache_Sorting_Planes(p_Var1);
    }
    Cache_Add_Geometry_To_Tree(pMVar4,lVar3);
    Cache_Add_All_Moving_Parts(local_904,Moving_Objects_Counter);
    param_1->Bsp_Container->Bsp_Geom = Root_Polygon;
  }
  return;
}
