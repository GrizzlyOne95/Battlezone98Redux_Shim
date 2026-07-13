/*
 * Entry: 005107f9
 * Name: Geom_VectorToAngle
 * Namespace: Global
 * Signature: int Geom_VectorToAngle(tagFLOATVEC2 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Geom_VectorToAngle(tagFLOATVEC2 *param_1)

{
  uint extraout_EAX;
  
  fpatan(-(float10)param_1->y,(float10)param_1->x);
  _ftol2_sse();
  return extraout_EAX & 0xffffff;
}
