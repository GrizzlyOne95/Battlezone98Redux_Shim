/*
 * Entry: 0052519b
 * Name: calc_collision_damage
 * Namespace: Global
 * Signature: float calc_collision_damage(_OBJ76 * param_1, _OBJ76 * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl
calc_collision_damage(_OBJ76 *param_1,_OBJ76 *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4)

{
  float fVar1;
  VECTOR_3D *in_EAX;
  VECTOR_3D *pVVar2;
  int iVar3;
  EULER *pEVar4;
  float *unaff_EBX;
  float10 fVar5;
  EULER local_64;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  pVVar2 = NegVector(&local_1c,*in_EAX);
  local_10 = pVVar2->x;
  local_c = pVVar2->y;
  local_8 = pVVar2->z;
  if (param_2 != (_OBJ76 *)0x0) {
    iVar3 = dynamic_object(param_2);
    if (iVar3 != 0) {
      pEVar4 = ClassGetEuler(&local_64,param_2);
      fVar1 = *unaff_EBX * local_10 + unaff_EBX[2] * local_8 + unaff_EBX[1] * local_c;
      fVar1 = fVar1 * fVar1 * pEVar4->mass * 0.25;
      goto LAB_00525234;
    }
  }
  pEVar4 = ClassGetEuler(&local_64,param_1);
  fVar1 = *unaff_EBX * local_10 + unaff_EBX[2] * local_8 + unaff_EBX[1] * local_c;
  fVar1 = fVar1 * fVar1 * pEVar4->mass * 0.375;
LAB_00525234:
  fVar5 = (float10)floor((double)(fVar1 * 0.0001));
  return (float)fVar5;
}
