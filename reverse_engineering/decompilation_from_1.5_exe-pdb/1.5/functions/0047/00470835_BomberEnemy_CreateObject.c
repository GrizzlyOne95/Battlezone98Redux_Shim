/*
 * Entry: 00470835
 * Name: BomberEnemy::CreateObject
 * Namespace: BomberEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl BomberEnemy::CreateObject(void)

{
  WingmanProcess *this;
  
  this = operator_new(0x78);
  if (this != (WingmanProcess *)0x0) {
    WingmanProcess::WingmanProcess(this);
    *(undefined ***)this = &_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
