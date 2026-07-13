/*
 * Entry: 004ea455
 * Name: Object_WorldSphere
 * Namespace: Global
 * Signature: SPHERE * Object_WorldSphere(SPHERE * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SPHERE * __cdecl Object_WorldSphere(SPHERE *__return_storage_ptr__,_OBJ76 *param_1)

{
  tagENTITY *ptVar1;
  MAT_3D *pMVar2;
  int iVar3;
  MAT_3D *pMVar4;
  MAT_3D local_90;
  MAT_3D local_50;
  
  ptVar1 = FindObjectEntity(param_1);
  if (ptVar1 == (tagENTITY *)0x0) {
    __return_storage_ptr__->radius = 0.0;
    (__return_storage_ptr__->origin).x = 0.0;
    (__return_storage_ptr__->origin).y = 0.0;
    (__return_storage_ptr__->origin).z = 0.0;
  }
  else {
    __return_storage_ptr__->radius = (ptVar1->bSphere).radius;
    if ((ptVar1->obj76->flags & 0x100) == 0) {
      pMVar2 = &ptVar1->obj76->transform;
    }
    else {
      pMVar2 = obj_rel_parent_matrix(&local_90,param_1,(_OBJ76 *)0x0);
    }
    pMVar4 = &local_50;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    Vector_Transform(&__return_storage_ptr__->origin,&(ptVar1->bSphere).origin,1,&local_50);
  }
  return __return_storage_ptr__;
}
