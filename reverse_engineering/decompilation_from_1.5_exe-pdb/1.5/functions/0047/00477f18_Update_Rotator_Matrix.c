/*
 * Entry: 00477f18
 * Name: Update_Rotator_Matrix
 * Namespace: Global
 * Signature: void Update_Rotator_Matrix(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Update_Rotator_Matrix(CAMERA *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  fVar1 = -(param_1->Matrix).right_z;
  fVar3 = -(param_1->Matrix).front_z;
  fVar2 = fVar3 * fVar3 + fVar1 * fVar1;
  fVar4 = 0.0;
  if (1e-05 <= fVar2) {
    dVar5 = rsqrt((double)fVar2);
    Rot_Mat.right_x = fVar3 * (float)dVar5;
    fVar4 = (float)dVar5 * fVar1;
  }
  else {
    Rot_Mat.right_x = -1.0;
  }
  Rot_Mat.right_y = 0.0;
  Rot_Mat.right_z = -fVar4;
  Rot_Mat.up_x = 0.0;
  Rot_Mat.up_y = 1.0;
  Rot_Mat.up_z = 0.0;
  Rot_Mat.front_y = 0.0;
  Rot_Mat.front_x = fVar4;
  Rot_Mat.front_z = Rot_Mat.right_x;
  return;
}
