/*
 * Entry: 005107e3
 * Name: Geom_VectorMagnitude
 * Namespace: Global
 * Signature: float Geom_VectorMagnitude(tagFLOATVEC2 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Geom_VectorMagnitude(tagFLOATVEC2 *param_1)

{
  return SQRT(param_1->x * param_1->x + param_1->y * param_1->y);
}
