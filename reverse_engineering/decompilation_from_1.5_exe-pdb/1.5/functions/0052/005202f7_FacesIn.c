/*
 * Entry: 005202f7
 * Name: FacesIn
 * Namespace: Global
 * Signature: int FacesIn(VECTOR_3D * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FacesIn(VECTOR_3D *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4)

{
  uint uVar1;
  
  uVar1 = (uint)(((uint)((param_2->y * param_1->z - param_2->z * param_1->y) * param_3->x +
                        (param_2->x * param_1->y - param_1->x * param_2->y) * param_3->z +
                        (param_1->x * param_2->z - param_2->x * param_1->z) * param_3->y) &
                 0x80000000) != 0);
  if (((uint)((param_1->z * param_3->y - param_1->y * param_3->z) * param_4->x +
             (param_1->x * param_3->z - param_3->x * param_1->z) * param_4->y +
             (param_3->x * param_1->y - param_1->x * param_3->y) * param_4->z) & 0x80000000) != 0) {
    uVar1 = uVar1 | 2;
  }
  return uVar1;
}
