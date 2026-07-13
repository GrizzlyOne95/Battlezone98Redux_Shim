/*
 * Entry: 00466ee8
 * Name: TugEnemy::TugEnemy
 * Namespace: TugEnemy
 * Signature: TugEnemy * TugEnemy(TugEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TugEnemy * __thiscall TugEnemy::TugEnemy(TugEnemy *this)

{
  TugProcess::TugProcess((TugProcess *)this);
  *(undefined4 *)&this->field_0x34 = 0x41200000;
  *(undefined ***)this = &_vftable_;
  return this;
}
