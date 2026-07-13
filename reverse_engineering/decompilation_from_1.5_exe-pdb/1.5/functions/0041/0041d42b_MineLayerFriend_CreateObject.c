/*
 * Entry: 0041d42b
 * Name: MineLayerFriend::CreateObject
 * Namespace: MineLayerFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MineLayerFriend::CreateObject(void)

{
  MineLayerProcess *this;
  
  this = operator_new(0x58);
  if (this != (MineLayerProcess *)0x0) {
    MineLayerProcess::MineLayerProcess(this);
    *(undefined ***)this = &_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
