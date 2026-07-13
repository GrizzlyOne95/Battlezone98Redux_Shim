/*
 * Entry: 0040c427
 * Name: GetApproachAim
 * Namespace: Global
 * Signature: float GetApproachAim(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetApproachAim(_OBJ76 *param_1,_OBJ76 *param_2)

{
  float fVar1;
  int iVar2;
  _OBJ76 *unaff_EBX;
  float10 fVar3;
  float fVar4;
  VECTOR_3D local_54;
  VECTOR_3D local_48;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_48.x = (float)(param_1->transform).posit_x;
  local_48.y = (float)(param_1->transform).posit_y;
  local_48.z = (float)(param_1->transform).posit_z;
  local_30.x = (float)(unaff_EBX->transform).posit_x;
  local_30.y = (float)(unaff_EBX->transform).posit_y;
  local_30.z = (float)(unaff_EBX->transform).posit_z;
  local_24.x = local_30.x;
  local_24.y = local_30.y;
  local_24.z = local_30.z;
  local_18 = local_48.x;
  local_14 = local_48.y;
  local_10 = local_48.z;
  iVar2 = is_vhcl(unaff_EBX);
  if (iVar2 != 0) {
    ClassGetVelocity(param_1,&local_3c,&local_8);
    ClassGetVelocity(unaff_EBX,&local_30,&local_c);
    fVar4 = closest_approach(&local_48,&local_3c,&local_24,&local_30);
    fVar1 = 0.01;
    if ((fVar4 < 0.01) || (fVar1 = 5.0, 5.0 < fVar4)) {
      fVar4 = fVar1;
    }
    est_pos(unaff_EBX,fVar4,&local_54);
    local_24.x = local_54.x;
    local_24.z = local_54.z;
  }
  fVar3 = (float10)fpatan((float10)local_24.x - (float10)local_18,
                          (float10)local_24.z - (float10)local_10);
  return (float)fVar3;
}
