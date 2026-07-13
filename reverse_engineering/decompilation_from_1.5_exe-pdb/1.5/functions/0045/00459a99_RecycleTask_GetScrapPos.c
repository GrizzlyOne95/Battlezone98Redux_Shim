/*
 * Entry: 00459a99
 * Name: RecycleTask_GetScrapPos
 * Namespace: Global
 * Signature: VECTOR_3D * RecycleTask_GetScrapPos(VECTOR_3D * __return_storage_ptr__, AiTask * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl RecycleTask_GetScrapPos(VECTOR_3D *__return_storage_ptr__,AiTask *param_1)

{
  __return_storage_ptr__->x = (float)param_1[4].user;
  __return_storage_ptr__->y = (float)param_1[5]._padding_;
  __return_storage_ptr__->z = (float)param_1[5]._padding_;
  return __return_storage_ptr__;
}
