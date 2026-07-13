/*
 * Entry: 00406f41
 * Name: AIUtil_Detect_2D_Collision_With_NonMoving_Object
 * Namespace: Global
 * Signature: int AIUtil_Detect_2D_Collision_With_NonMoving_Object(GameObject * param_1, GameObject * param_2, float param_3, VECTOR_3D param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIUtil_Detect_2D_Collision_With_NonMoving_Object
          (GameObject *param_1,GameObject *param_2,float param_3,VECTOR_3D param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float *pfVar13;
  
  fVar7 = (param_1->collisionRadius + param_2->collisionRadius) * COLLISION_SAFETY_COEFF;
  fVar1 = (param_1->euler).v_mag;
  pfVar13 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar2 = *pfVar13;
  fVar3 = pfVar13[1];
  fVar4 = pfVar13[2];
  pfVar13 = (float *)(**(code **)(param_2->_padding_ + 0xc))();
  fVar8 = param_4.x - fVar2;
  fVar3 = param_4.y - fVar3;
  fVar12 = param_4.z - fVar4;
  fVar9 = -fVar8;
  fVar5 = fVar2 - *pfVar13;
  fVar6 = fVar4 - pfVar13[2];
  fVar2 = *pfVar13 - fVar2;
  fVar4 = pfVar13[2] - fVar4;
  fVar11 = SQRT(fVar9 * fVar9 + fVar12 * fVar12);
  if (0.0001 <= fVar11) {
    fVar10 = SQRT(fVar8 * fVar8 + fVar3 * fVar3 + fVar12 * fVar12);
    fVar3 = (fVar4 * fVar12 + fVar2 * fVar8 + fVar3 * 0.0) / fVar10;
    if ((((ABS((fVar12 * fVar2 + fVar4 * fVar9) / fVar11) <= LATERAL_DANGER_WIDTH * fVar7) &&
         (0.0 < fVar3)) && (fVar3 <= fVar1 * param_3)) &&
       ((0.0 < fVar1 && (fVar5 * fVar5 + fVar6 * fVar6 <= fVar10 * fVar10)))) {
      return 1;
    }
  }
  return 0;
}
