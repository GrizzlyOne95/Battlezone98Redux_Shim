/*
 * Entry: 004f0b53
 * Name: Camera_Init
 * Namespace: Global
 * Signature: CAMERA * Camera_Init(CAMERA * __return_storage_ptr__, _GRAPHIC_BUFFER * param_1, float param_2, float param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CAMERA * __cdecl
Camera_Init(CAMERA *__return_storage_ptr__,_GRAPHIC_BUFFER *param_1,float param_2,float param_3,
           float param_4,float param_5)

{
  int iVar1;
  MAT_3D *pMVar2;
  MAT_3D *pMVar3;
  float10 fVar4;
  float10 fVar5;
  MAT_3D local_54;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  memset(__return_storage_ptr__,0,0x1d8);
  fVar4 = (float10)param_2;
  __return_storage_ptr__->Buffer = param_1;
  if (fVar4 < (float10)0.7853982) {
    fVar4 = (float10)0.7853982;
  }
  if ((float10)2.3561945 < fVar4) {
    fVar4 = (float10)2.3561945;
  }
  if (param_4 < 100.0) {
    param_4 = 100.0;
  }
  if (1640.0 < param_4) {
    param_4 = 1640.0;
  }
  iVar1 = param_1->Height;
  fVar5 = (float10)0.5;
  __return_storage_ptr__->Orig_x =
       (float)((float10)(((param_1->Pane).x1 - (param_1->Pane).x0) + 1) * fVar5);
  __return_storage_ptr__->Orig_y = (float)((float10)iVar1 * fVar5);
  __return_storage_ptr__->Max_Depth = param_4;
  __return_storage_ptr__->View_Angle = (float)fVar4;
  fVar4 = (float10)fptan(fVar4 * fVar5);
  __return_storage_ptr__->Tang = (float)(fVar4 * (float10)0.75);
  __return_storage_ptr__->Aspect = param_3;
  local_14 = (param_1->Pane).x0;
  local_10 = (param_1->Pane).y0;
  local_c = (param_1->Pane).x1;
  local_8 = (param_1->Pane).y1;
  __return_storage_ptr__->Left = (float)local_14;
  __return_storage_ptr__->Bottom = (float)local_10;
  __return_storage_ptr__->Right = (float)local_c;
  __return_storage_ptr__->Top = (float)local_8;
  Camera_Set_Zoom(__return_storage_ptr__,param_5);
  pMVar2 = &Identity_Matrix;
  pMVar3 = &local_54;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar3->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  local_54.posit_x = 0.0;
  local_54.posit_y = 1.0;
  local_54.posit_z = 0.0;
  Camera_Set_Matrix(__return_storage_ptr__,&local_54);
  return __return_storage_ptr__;
}
