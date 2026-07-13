/*
 * Entry: 004639a7
 * Name: TorpedoProcess::~TorpedoProcess
 * Namespace: TorpedoProcess
 * Signature: void ~TorpedoProcess(TorpedoProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TorpedoProcess::~TorpedoProcess(TorpedoProcess *this)

{
  *(undefined ***)this = &_vftable_;
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
