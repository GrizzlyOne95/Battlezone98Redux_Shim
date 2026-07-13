/*
 * Entry: 004e9557
 * Name: Cache_Transform_Vertex_List
 * Namespace: Global
 * Signature: void Cache_Transform_Vertex_List(_OBJ76 * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Transform_Vertex_List(_OBJ76 *param_1,MAT_3D *param_2)

{
  int in_EAX;
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *unaff_EBX;
  MAT_3D *pMVar3;
  _GEOMETRY *p_Var4;
  MAT_3D local_8c;
  MAT_3D local_4c;
  int local_c;
  float *local_8;
  
  local_c = *(int *)(in_EAX + 100);
  if (*(int *)(local_c + 0x14) != 0) {
    local_8 = Luma_Base_Entry + Entity_Vertex_Count;
    pMVar1 = unaff_EBX;
    if ((*(byte *)(in_EAX + 0x14) & 0x40) != 0) {
      Rot_Mat.posit_x = unaff_EBX->posit_x;
      Rot_Mat.posit_y = unaff_EBX->posit_y;
      Rot_Mat.posit_z = unaff_EBX->posit_z;
      pMVar1 = &Rot_Mat;
    }
    pMVar1 = Matrix_Multiply(&local_8c,pMVar1,&Local_Camera->Matrix);
    p_Var4 = (_GEOMETRY *)(Vertex_Pool + Entity_Vertex_Count);
    pMVar3 = &local_4c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar3->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
    }
    pMVar1 = *(MAT_3D **)(local_c + 0xc);
    Vector_Transform((VECTOR_3D *)p_Var4,(VECTOR_3D *)pMVar1,*(long *)(local_c + 4),&local_4c);
    Apply_Simple_Light_Model(Vertex_Pool + Entity_Vertex_Count,&unaff_EBX->right_x,p_Var4,pMVar1);
  }
  return;
}
