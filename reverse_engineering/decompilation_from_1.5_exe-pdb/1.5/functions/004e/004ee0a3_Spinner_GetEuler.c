/*
 * Entry: 004ee0a3
 * Name: Spinner_GetEuler
 * Namespace: Global
 * Signature: EULER * Spinner_GetEuler(EULER * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EULER * __cdecl Spinner_GetEuler(EULER *__return_storage_ptr__,_OBJ76 *param_1)

{
  float *pfVar1;
  
  pfVar1 = param_1->class_ptr;
  InitEuler(__return_storage_ptr__);
  (__return_storage_ptr__->omega).x = *pfVar1;
  (__return_storage_ptr__->omega).y = pfVar1[1];
  (__return_storage_ptr__->omega).z = pfVar1[2];
  return __return_storage_ptr__;
}
