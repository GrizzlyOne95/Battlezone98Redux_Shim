/*
 * Entry: 004ca06e
 * Name: EditTerrain::WorldToScreen
 * Namespace: EditTerrain
 * Signature: tagPOINT WorldToScreen(EditTerrain * this, VECTOR_3D * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagPOINT __thiscall EditTerrain::WorldToScreen(EditTerrain *this,VECTOR_3D *param_1,CAMERA *param_2)

{
  float fVar1;
  float fVar2;
  long extraout_EDX;
  tagPOINT tVar3;
  float *in_stack_0000000c;
  VECTOR_3D local_18;
  float local_c;
  
  Vector_Transform(&local_18,(VECTOR_3D *)param_2,1,(MAT_3D *)(in_stack_0000000c + 0x10));
  if (local_18.z <= 1.0) {
    local_c = SUB84((double)(in_stack_0000000c[2] * local_18.x + *in_stack_0000000c +
                            (float)Float2Int),0);
    fVar1 = in_stack_0000000c[3];
  }
  else {
    local_c = SUB84((double)(in_stack_0000000c[2] * (1.0 / local_18.z) * local_18.x +
                             *in_stack_0000000c + (float)Float2Int),0);
    fVar1 = in_stack_0000000c[3] * (1.0 / local_18.z);
  }
  fVar2 = (float)Float2Int;
  param_1->x = local_c;
  local_18.y = SUB84((double)(fVar1 * local_18.y + in_stack_0000000c[1] + fVar2),0);
  param_1->y = local_18.y;
  tVar3.y = extraout_EDX;
  tVar3.x = (long)param_1;
  return tVar3;
}
