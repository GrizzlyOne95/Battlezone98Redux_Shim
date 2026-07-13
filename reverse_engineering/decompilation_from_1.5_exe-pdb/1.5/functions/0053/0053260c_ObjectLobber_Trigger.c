/*
 * Entry: 0053260c
 * Name: ObjectLobber::Trigger
 * Namespace: ObjectLobber
 * Signature: void Trigger(ObjectLobber * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ObjectLobber::Trigger(ObjectLobber *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
