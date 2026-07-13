/*
 * Entry: 004118b2
 * Name: MUFFriend::~MUFFriend
 * Namespace: MUFFriend
 * Signature: void ~MUFFriend(MUFFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MUFFriend::~MUFFriend(MUFFriend *this)

{
  *(undefined ***)this = &RecyclerProcess::_vftable_;
  RecyclerProcess::CleanState((RecyclerProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
