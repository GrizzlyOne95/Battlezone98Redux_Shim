/*
 * Entry: 0045dbf7
 * Name: ScavengerEnemy::CreateObject
 * Namespace: ScavengerEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl ScavengerEnemy::CreateObject(void)

{
  ScavengerProcess *this;
  
  this = operator_new(0x58);
  if (this != (ScavengerProcess *)0x0) {
    ScavengerProcess::ScavengerProcess(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
