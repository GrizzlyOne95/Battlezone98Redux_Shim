/*
 * Entry: 004c187e
 * Name: WorldToScreen
 * Namespace: Global
 * Signature: tagPOINT WorldToScreen(VECTOR_3D * param_1, CAMERA * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagPOINT __cdecl WorldToScreen(VECTOR_3D *param_1,CAMERA *param_2,float *param_3)

{
  float fVar1;
  tagPOINT tVar2;
  VECTOR_3D local_18;
  long local_c;
  
  Vector_Transform(&local_18,param_1,1,&param_2->Matrix);
  if (local_18.z <= 1.0) {
    local_c = SUB84((double)(param_2->Const_x * local_18.x + param_2->Orig_x + (float)Float2Int),0);
    fVar1 = param_2->Const_y * local_18.y + param_2->Orig_y + (float)Float2Int;
  }
  else {
    local_c = SUB84((double)(param_2->Const_x * (1.0 / local_18.z) * local_18.x + param_2->Orig_x +
                            (float)Float2Int),0);
    fVar1 = param_2->Const_y * (1.0 / local_18.z) * local_18.y + param_2->Orig_y + (float)Float2Int;
  }
  if (param_3 != (float *)0x0) {
    if (local_18.z == 0.0) {
      local_18.z = 1e+30;
    }
    else {
      local_18.z = param_2->Const_x / local_18.z;
    }
    *param_3 = local_18.z;
  }
  local_18.y = SUB84((double)fVar1,0);
  tVar2.y = (long)local_18.y;
  tVar2.x = local_c;
  return tVar2;
}
