/*
 * Entry: 00532c2e
 * Name: Ordnance::Expired
 * Namespace: Ordnance
 * Signature: bool Expired(Ordnance * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Ordnance::Expired(Ordnance *this)

{
  return (bool)((byte)(this->obj->flags >> 9) & 1);
}
