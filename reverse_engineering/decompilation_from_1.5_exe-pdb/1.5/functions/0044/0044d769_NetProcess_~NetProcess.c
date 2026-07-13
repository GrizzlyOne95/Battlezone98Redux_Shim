/*
 * Entry: 0044d769
 * Name: NetProcess::~NetProcess
 * Namespace: NetProcess
 * Signature: void ~NetProcess(NetProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall NetProcess::~NetProcess(NetProcess *this)

{
  *(undefined ***)this = &_vftable_;
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
