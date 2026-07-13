/*
 * Entry: 004ed7d5
 * Name: Get_Scrounge_Pos
 * Namespace: Global
 * Signature: VECTOR_3D * Get_Scrounge_Pos(VECTOR_3D * __return_storage_ptr__, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl Get_Scrounge_Pos(VECTOR_3D *__return_storage_ptr__,CAMERA *param_1)

{
  double dVar1;
  int in_EAX;
  float fVar2;
  
  if (((((float)*(double *)(in_EAX + 0x160) - Scrounge_Pos.x < 0.0) ||
       (0.0 < (float)*(double *)(in_EAX + 0x160) - (Scrounge_Pos.x + 100.0))) ||
      ((float)*(double *)(in_EAX + 0x170) - Scrounge_Pos.z < 0.0)) ||
     (0.0 < (float)*(double *)(in_EAX + 0x170) - (Scrounge_Pos.z + 100.0))) {
    dVar1 = *(double *)(in_EAX + 0x160);
    fVar2 = Fmod1((float)dVar1,100.0);
    Scrounge_Pos.x = (float)dVar1 - fVar2;
    dVar1 = *(double *)(in_EAX + 0x170);
    fVar2 = Fmod1((float)dVar1,100.0);
    Scrounge_Pos.z = (float)dVar1 - fVar2;
  }
  __return_storage_ptr__->x = Scrounge_Pos.x;
  __return_storage_ptr__->y = Scrounge_Pos.y;
  __return_storage_ptr__->z = Scrounge_Pos.z;
  return __return_storage_ptr__;
}
