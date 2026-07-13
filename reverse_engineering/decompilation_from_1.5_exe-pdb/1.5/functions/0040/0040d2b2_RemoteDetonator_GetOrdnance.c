/*
 * Entry: 0040d2b2
 * Name: RemoteDetonator::GetOrdnance
 * Namespace: RemoteDetonator
 * Signature: Ordnance * GetOrdnance(RemoteDetonator * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall RemoteDetonator::GetOrdnance(RemoteDetonator *this,int param_1)

{
  return this->ordnance[param_1];
}
