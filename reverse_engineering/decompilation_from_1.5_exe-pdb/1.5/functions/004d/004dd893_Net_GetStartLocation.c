/*
 * Entry: 004dd893
 * Name: Net_GetStartLocation
 * Namespace: Global
 * Signature: VECTOR_3D * Net_GetStartLocation(VECTOR_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl Net_GetStartLocation(VECTOR_3D *__return_storage_ptr__)

{
  VECTOR_3D *pVVar1;
  Net *pNVar2;
  
  pNVar2 = theNet;
  pVVar1 = &theNet->start_location;
  __return_storage_ptr__->x = (theNet->start_location).x;
  __return_storage_ptr__->y = pVVar1->y;
  __return_storage_ptr__->z = (pNVar2->start_location).z;
  return __return_storage_ptr__;
}
