/*
 * Entry: 0044d757
 * Name: NetProcess::NetProcess
 * Namespace: NetProcess
 * Signature: NetProcess * NetProcess(NetProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NetProcess * __thiscall NetProcess::NetProcess(NetProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
