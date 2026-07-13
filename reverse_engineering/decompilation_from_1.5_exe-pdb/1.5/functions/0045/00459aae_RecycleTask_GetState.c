/*
 * Entry: 00459aae
 * Name: RecycleTask_GetState
 * Namespace: Global
 * Signature: RecycleTask_State RecycleTask_GetState(AiTask * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecycleTask_State __cdecl RecycleTask_GetState(AiTask *param_1)

{
  if (param_1[6]._padding_ == 2) {
    return RecycleTask_Pickup;
  }
  if (param_1[6]._padding_ != 3) {
    return RecycleTask_Other;
  }
  return RecycleTask_Dropoff;
}
