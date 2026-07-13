/*
 * Entry: 00466f03
 * Name: TugEnemy::~TugEnemy
 * Namespace: TugEnemy
 * Signature: void ~TugEnemy(TugEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugEnemy::~TugEnemy(TugEnemy *this)

{
  *(undefined ***)this = &TugProcess::_vftable_;
  TugProcess::CleanState((TugProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
