/*
 * Entry: 0047a692
 * Name: Get_Chase_Quaternion
 * Namespace: Global
 * Signature: QUAT * Get_Chase_Quaternion(QUAT * __return_storage_ptr__, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QUAT * __cdecl Get_Chase_Quaternion(QUAT *__return_storage_ptr__,tagENTITY *param_1)

{
  QUAT *pQVar1;
  MAT_3D *unaff_EDI;
  QUAT local_14;
  
  pQVar1 = Get_Matrix_Quaternion(&local_14,unaff_EDI);
  (__return_storage_ptr__->n).x = (pQVar1->n).x;
  (__return_storage_ptr__->n).y = (pQVar1->n).y;
  (__return_storage_ptr__->n).z = (pQVar1->n).z;
  __return_storage_ptr__->w = pQVar1->w;
  return __return_storage_ptr__;
}
