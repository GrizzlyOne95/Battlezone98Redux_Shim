/*
 * Entry: 0041d44f
 * Name: MineLayerEnemy::CreateObject
 * Namespace: MineLayerEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MineLayerEnemy::CreateObject(void)

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
