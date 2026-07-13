/*
 * Entry: 00463995
 * Name: TorpedoProcess::TorpedoProcess
 * Namespace: TorpedoProcess
 * Signature: TorpedoProcess * TorpedoProcess(TorpedoProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TorpedoProcess * __thiscall TorpedoProcess::TorpedoProcess(TorpedoProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
