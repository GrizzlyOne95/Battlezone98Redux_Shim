/*
 * Entry: 004e8a24
 * Name: SubdivideTriangle
 * Namespace: Global
 * Signature: int SubdivideTriangle(VECTOR_3D * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
SubdivideTriangle(VECTOR_3D *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,int param_4,int param_5)

{
  int iVar1;
  long unaff_EDI;
  VECTOR_3D local_10;
  
  local_10.x = (param_1->x + param_2->x + param_3->x) * 0.33333334;
  local_10.y = (param_1->y + param_2->y + param_3->y) * 0.33333334;
  Screen_Draw_Pixel(Local_Camera,(VECTOR_3D *)param_4,unaff_EDI);
  iVar1 = param_5 + -1;
  if (iVar1 != 0) {
    SubdivideTriangle(param_1,param_2,&local_10,param_4,iVar1);
    SubdivideTriangle(param_2,param_3,&local_10,param_4,iVar1);
    SubdivideTriangle(param_3,param_1,&local_10,param_4,iVar1);
  }
  return 0;
}
