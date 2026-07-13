/*
 * Entry: 004ee182
 * Name: Spinner_SetRate
 * Namespace: Global
 * Signature: void Spinner_SetRate(_OBJ76 * param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Spinner_SetRate(_OBJ76 *param_1,VECTOR_3D param_2)

{
  float *pfVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D local_10;
  
  pVVar2 = ScaleVector(&local_10,6.2831855,param_2);
  pfVar1 = param_1->class_ptr;
  *pfVar1 = pVVar2->x;
  pfVar1[1] = pVVar2->y;
  pfVar1[2] = pVVar2->z;
  return;
}
