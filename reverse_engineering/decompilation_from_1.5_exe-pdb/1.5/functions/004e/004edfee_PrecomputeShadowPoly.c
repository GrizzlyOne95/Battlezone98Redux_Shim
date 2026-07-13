/*
 * Entry: 004edfee
 * Name: PrecomputeShadowPoly
 * Namespace: Global
 * Signature: void PrecomputeShadowPoly(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PrecomputeShadowPoly(tagENTITY *param_1)

{
  float fVar1;
  
  param_1->shadowPoly[0].x = (param_1->bBox).min.x;
  fVar1 = ((param_1->bBox).max.y + (param_1->bBox).min.y) * 0.5;
  param_1->shadowPoly[0].y = fVar1;
  param_1->shadowPoly[0].z = (param_1->bBox).min.z;
  param_1->shadowPoly[1].x = (param_1->bBox).max.x;
  param_1->shadowPoly[1].y = fVar1;
  param_1->shadowPoly[1].z = (param_1->bBox).min.z;
  param_1->shadowPoly[2].x = (param_1->bBox).max.x;
  param_1->shadowPoly[2].y = fVar1;
  param_1->shadowPoly[2].z = (param_1->bBox).max.z;
  param_1->shadowPoly[3].x = (param_1->bBox).min.x;
  param_1->shadowPoly[3].y = fVar1;
  param_1->shadowPoly[3].z = (param_1->bBox).max.z;
  return;
}
