/*
 * Entry: 0053880b
 * Name: SeismicWaveClass::SeismicWaveClass
 * Namespace: SeismicWaveClass
 * Signature: SeismicWaveClass * SeismicWaveClass(SeismicWaveClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SeismicWaveClass * __thiscall SeismicWaveClass::SeismicWaveClass(SeismicWaveClass *this)

{
  OrdnanceClass::OrdnanceClass((OrdnanceClass *)this);
  this->_padding_ = 0x43480000;
  this->waveRadius = 50.0;
  *(undefined2 *)&this->_padding_ = 8;
  this->_padding_ = (int)&_vftable_;
  this->waveRadiusInv = 0.02;
  this->_padding_ = 0x53454953;
  this->_padding_ = (int)"seismic";
  this->waveRadiusExp = -0.001;
  this->waveHeight = 6.0;
  this->startOffset = 0.0;
  this->rampUpTime = 5.0;
  this->rampUpRate = 0.2;
  this->rampDownTime = 2.0;
  this->rampDownRate = 0.5;
  this->sweepOmega = 100.0;
  this->sweepVeloc = 50.0;
  this->shakeFrequency = 3.0;
  this->shakeOmega = 2.0;
  this->shakeVeloc = 5.0;
  this->walkerScale = 1.0;
  this->towerScale = 1.0;
  this->buildingScale = 1.0;
  this->dampOmega = 0.0;
  this->levelOmega = 0.0;
  return this;
}
