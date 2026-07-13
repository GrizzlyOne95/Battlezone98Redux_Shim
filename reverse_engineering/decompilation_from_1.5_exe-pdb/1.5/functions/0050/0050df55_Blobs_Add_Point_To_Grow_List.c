/*
 * Entry: 0050df55
 * Name: Blobs_Add_Point_To_Grow_List
 * Namespace: Global
 * Signature: void Blobs_Add_Point_To_Grow_List(ushort * * param_1, _coloring_point * * param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blobs_Add_Point_To_Grow_List
          (ushort **param_1,_coloring_point **param_2,int param_3,int param_4,int param_5)

{
  int in_EAX;
  _coloring_point *p_Var1;
  undefined4 *unaff_EBX;
  int unaff_ESI;
  int unaff_EDI;
  
  *(undefined2 *)(*(int *)(in_EAX + unaff_EDI * 4) + unaff_ESI * 2) = param_1._0_2_;
  if (point_head == (_coloring_point *)0x0) {
    p_Var1 = calloc(1,8);
    point_count = point_count + 1;
  }
  else {
    p_Var1 = point_head;
    point_head = point_head->next;
  }
  p_Var1->row = (ushort)unaff_EDI;
  p_Var1->column = (ushort)unaff_ESI;
  p_Var1->next = (_coloring_point *)*unaff_EBX;
  *unaff_EBX = p_Var1;
  return;
}
