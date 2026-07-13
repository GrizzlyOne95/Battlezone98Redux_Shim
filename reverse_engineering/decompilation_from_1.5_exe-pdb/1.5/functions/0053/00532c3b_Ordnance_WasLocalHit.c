/*
 * Entry: 00532c3b
 * Name: Ordnance::WasLocalHit
 * Namespace: Ordnance
 * Signature: bool WasLocalHit(Ordnance * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Ordnance::WasLocalHit(Ordnance *this)

{
  return (bool)((byte)(this->obj->flags >> 1) & 1);
}
