/*
 * Entry: 004e7182
 * Name: SpawnPoint::AddSpawnPoint
 * Namespace: SpawnPoint
 * Signature: void AddSpawnPoint(VECTOR_3D param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SpawnPoint::AddSpawnPoint(VECTOR_3D param_1,int param_2)

{
  SpawnPoint *this;
  
  this = operator_new(0x14);
  if (this != (SpawnPoint *)0x0) {
    SpawnPoint(this,param_1,param_2);
  }
  return;
}
