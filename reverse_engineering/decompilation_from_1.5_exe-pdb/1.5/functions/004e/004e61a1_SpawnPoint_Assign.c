/*
 * Entry: 004e61a1
 * Name: SpawnPoint::Assign
 * Namespace: SpawnPoint
 * Signature: void Assign(SpawnPoint * this, NetPlayer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpawnPoint::Assign(SpawnPoint *this,NetPlayer *param_1)

{
  this[1].location.x = (float)param_1;
  return;
}
