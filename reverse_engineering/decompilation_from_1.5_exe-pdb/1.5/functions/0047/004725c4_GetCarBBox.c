/*
 * Entry: 004725c4
 * Name: GetCarBBox
 * Namespace: Global
 * Signature: BBOX * GetCarBBox(BBOX * __return_storage_ptr__, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BBOX * __cdecl GetCarBBox(BBOX *__return_storage_ptr__,tagENTITY *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = param_1->clsnDetails;
  if (piVar1 != (int *)0x0) {
    iVar2 = *piVar1;
    (__return_storage_ptr__->min).x = (float)piVar1[3];
    (__return_storage_ptr__->min).y = (float)piVar1[7];
    (__return_storage_ptr__->min).z = (float)piVar1[0xb];
    iVar3 = piVar1[1];
    (__return_storage_ptr__->max).x = (float)piVar1[iVar2 + 2];
    iVar2 = piVar1[2];
    (__return_storage_ptr__->max).y = (float)piVar1[iVar3 + 6];
    (__return_storage_ptr__->max).z = (float)piVar1[iVar2 + 10];
    return __return_storage_ptr__;
  }
  (__return_storage_ptr__->max).x = 0.0;
  (__return_storage_ptr__->max).y = 0.0;
  (__return_storage_ptr__->max).z = 0.0;
  (__return_storage_ptr__->min).x = 0.0;
  (__return_storage_ptr__->min).y = 0.0;
  (__return_storage_ptr__->min).z = 0.0;
  return __return_storage_ptr__;
}
