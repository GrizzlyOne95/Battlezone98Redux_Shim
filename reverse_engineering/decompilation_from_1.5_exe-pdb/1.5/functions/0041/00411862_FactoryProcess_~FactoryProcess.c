/*
 * Entry: 00411862
 * Name: FactoryProcess::~FactoryProcess
 * Namespace: FactoryProcess
 * Signature: void ~FactoryProcess(FactoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FactoryProcess::~FactoryProcess(FactoryProcess *this)

{
  *(undefined ***)this = &RecyclerProcess::_vftable_;
  RecyclerProcess::CleanState((RecyclerProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
