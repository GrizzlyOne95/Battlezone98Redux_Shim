/*
 * Entry: 00412cdf
 * Name: GechProcess::GechProcess
 * Namespace: GechProcess
 * Signature: GechProcess * GechProcess(GechProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GechProcess * __thiscall GechProcess::GechProcess(GechProcess *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
