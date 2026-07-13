/*
 * Entry: 004dd3a3
 * Name: Net::SetMyPlayerId
 * Namespace: Net
 * Signature: void SetMyPlayerId(Net * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::SetMyPlayerId(Net *this,ushort param_1)

{
  myPlayerID = param_1;
  DistributedObject_SetGlobalPlayerID(param_1);
  return;
}
