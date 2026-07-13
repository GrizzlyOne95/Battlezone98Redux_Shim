/*
 * Entry: 00406cb7
 * Name: AIUtil_Detect_2D_Collision
 * Namespace: Global
 * Signature: int AIUtil_Detect_2D_Collision(GameObject * param_1, GameObject * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIUtil_Detect_2D_Collision(GameObject *param_1,GameObject *param_2,float param_3)

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
  float *pfVar11;
  float10 fVar12;
  int local_8;
  
  local_8 = 0;
  fVar10 = (param_1->collisionRadius + param_2->collisionRadius) * COLLISION_SAFETY_COEFF;
  pfVar11 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar1 = *pfVar11;
  fVar2 = pfVar11[2];
  pfVar11 = (float *)(**(code **)(param_2->_padding_ + 0xc))();
  fVar3 = *pfVar11;
  fVar4 = pfVar11[2];
  fVar5 = (param_1->euler).v.x;
  fVar6 = (param_1->euler).v.z;
  fVar7 = (param_2->euler).v.x;
  fVar8 = (param_2->euler).v.z;
  fVar9 = SQRT((fVar1 - fVar3) * (fVar1 - fVar3) + (fVar2 - fVar4) * (fVar2 - fVar4)) - fVar10;
  if (fVar9 <= 0.0) {
    local_8 = 1;
  }
  else if (((fVar9 <= ((param_1->euler).v_mag + (param_2->euler).v_mag) * param_3) &&
           (fVar12 = (float10)__CIacos(), fVar12 < (float10)1.5707964)) &&
          ((float10)-1.5707964 < fVar12)) {
    fVar9 = (fVar6 * fVar6 + fVar8 * fVar8 + ((fVar5 * fVar5 + fVar7 * fVar7) - fVar7 * fVar5 * 2.0)
            ) - fVar8 * fVar6 * 2.0;
    fVar5 = fVar8 * fVar4 * 2.0 +
            (((fVar6 * fVar2 * 2.0 +
              fVar7 * fVar3 * 2.0 +
              ((fVar5 * fVar1 * 2.0 - fVar7 * fVar1 * 2.0) - fVar5 * fVar3 * 2.0)) -
             fVar8 * fVar2 * 2.0) - fVar6 * fVar4 * 2.0);
    if ((fVar9 != 0.0) &&
       (fVar1 = fVar5 * fVar5 -
                ((fVar4 * fVar4 +
                 ((fVar2 * fVar2 + (fVar1 * fVar1 - fVar3 * fVar1 * 2.0) + fVar3 * fVar3) -
                 fVar4 * fVar2 * 2.0)) - fVar10 * fVar10) * fVar9 * 4.0, 0.0 <= fVar1)) {
      fVar1 = SQRT(fVar1);
      fVar2 = (fVar1 - fVar5) / (fVar9 * 2.0);
      fVar1 = (-fVar5 - fVar1) / (fVar9 * 2.0);
      if (((!NAN(fVar2) && 0.0 < fVar2 != (fVar2 == 0.0)) && (fVar2 <= param_3)) ||
         ((0.0 <= fVar1 && (fVar1 < param_3 != (fVar1 == param_3))))) {
        local_8 = 1;
      }
    }
  }
  return local_8;
}
