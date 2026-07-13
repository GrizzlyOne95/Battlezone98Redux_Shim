/*
 * Entry: 004f0a65
 * Name: Camera_Set_Zoom
 * Namespace: Global
 * Signature: void Camera_Set_Zoom(CAMERA * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Camera_Set_Zoom(CAMERA *param_1,float param_2)

{
  float fVar1;
  long extraout_EAX;
  long extraout_EAX_00;
  long extraout_EAX_01;
  long extraout_EAX_02;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if (param_2 < 0.5) {
    param_2 = 0.5;
  }
  if (100.0 < param_2) {
    param_2 = 100.0;
  }
  param_1->Zoom_Factor = param_2;
  fVar1 = param_2 * (float)param_1->Buffer->Height * 0.5;
  param_1->Const_x = fVar1 / (param_1->Aspect * param_1->Tang);
  param_1->Const_y = -(fVar1 / param_1->Tang);
  _ftol2_sse();
  lVar4 = extraout_EAX;
  _ftol2_sse();
  lVar3 = extraout_EAX_00;
  _ftol2_sse();
  lVar2 = extraout_EAX_01;
  _ftol2_sse();
  Camera_Set_Clipping_Rect(param_1,extraout_EAX_02,lVar2,lVar3,lVar4);
  return;
}
