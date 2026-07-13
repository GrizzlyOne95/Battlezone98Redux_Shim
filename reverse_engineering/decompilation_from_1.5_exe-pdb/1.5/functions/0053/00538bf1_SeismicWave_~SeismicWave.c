/*
 * Entry: 00538bf1
 * Name: SeismicWave::~SeismicWave
 * Namespace: SeismicWave
 * Signature: void ~SeismicWave(SeismicWave * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SeismicWave::~SeismicWave(SeismicWave *this)

{
  this->_padding_ = (int)&_vftable_;
  operator_delete__(this->deltaH);
  Ordnance::~Ordnance((Ordnance *)this);
  return;
}
