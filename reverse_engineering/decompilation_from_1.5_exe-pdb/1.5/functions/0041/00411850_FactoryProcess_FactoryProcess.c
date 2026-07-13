/*
 * Entry: 00411850
 * Name: FactoryProcess::FactoryProcess
 * Namespace: FactoryProcess
 * Signature: FactoryProcess * FactoryProcess(FactoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FactoryProcess * __thiscall FactoryProcess::FactoryProcess(FactoryProcess *this)

{
  RecyclerProcess::RecyclerProcess((RecyclerProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
