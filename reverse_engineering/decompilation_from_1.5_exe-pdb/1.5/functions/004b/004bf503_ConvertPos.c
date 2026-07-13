/*
 * Entry: 004bf503
 * Name: ConvertPos
 * Namespace: Global
 * Signature: tagPOINT ConvertPos(VECTOR_3D * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagPOINT __cdecl ConvertPos(VECTOR_3D *param_1,float param_2)

{
  float fVar1;
  float *in_EAX;
  tagPOINT tVar2;
  int local_14;
  int local_c;
  
  fVar1 = ((float)RADAR_RADIUS * 2000.0) / ((in_EAX[2] + 2000.0) * (float)param_1);
  local_c = SUB84((double)(*in_EAX * fVar1 + (float)Float2Int),0);
  tVar2.x = local_c + RADAR_CENTER.x;
  local_14 = SUB84((double)((float)Float2Int + in_EAX[1] * fVar1),0);
  tVar2.y = RADAR_CENTER.y - local_14;
  return tVar2;
}
