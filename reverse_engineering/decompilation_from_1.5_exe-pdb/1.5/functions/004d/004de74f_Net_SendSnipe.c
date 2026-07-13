/*
 * Entry: 004de74f
 * Name: Net::SendSnipe
 * Namespace: Net
 * Signature: void SendSnipe(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net::SendSnipe(GameObject *param_1,GameObject *param_2)

{
  ushort uVar1;
  undefined2 local_1c;
  ulong local_1a;
  undefined4 local_16;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_1c = 0x736e;
  local_1a = DistributedObject::GetID((DistributedObject *)&param_2->_padding_);
  if (param_1 == (GameObject *)0x0) {
    local_16 = 0;
  }
  else {
    local_16 = (**(code **)(param_1->_padding_ + 4))();
  }
  uVar1 = DistributedObject::GetPlayerID((DistributedObject *)&param_2->_padding_);
  if (uVar1 != 0) {
    Send(dp,myPlayerID,uVar1,1,&local_1c,10);
  }
  return;
}
