/*
 * Entry: 004f0ae5
 * Name: Camera_Set_Window
 * Namespace: Global
 * Signature: void Camera_Set_Window(CAMERA * param_1, long param_2, long param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Camera_Set_Window(CAMERA *param_1,long param_2,long param_3,long param_4,long param_5)

{
  float fVar1;
  
  param_1->Orig_x = (float)(param_2 + param_4) * 0.5;
  param_1->Orig_y = (float)(param_3 + param_5) * 0.5;
  fVar1 = (float)(param_5 - param_3) * param_1->Zoom_Factor * 0.5;
  param_1->Const_x = fVar1 / (param_1->Aspect * param_1->Tang);
  param_1->Const_y = -(fVar1 / param_1->Tang);
  Camera_Set_Clipping_Rect(param_1,param_2,param_3,param_4,param_5);
  return;
}
