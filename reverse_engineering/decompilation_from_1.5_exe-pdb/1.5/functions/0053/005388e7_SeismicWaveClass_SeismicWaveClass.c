/*
 * Entry: 005388e7
 * Name: SeismicWaveClass::SeismicWaveClass
 * Namespace: SeismicWaveClass
 * Signature: SeismicWaveClass * SeismicWaveClass(SeismicWaveClass * this, SeismicWaveClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SeismicWaveClass * __thiscall
SeismicWaveClass::SeismicWaveClass(SeismicWaveClass *this,SeismicWaveClass *param_1,long64 param_2)

{
  float fVar1;
  SeismicWaveClass *pSVar2;
  undefined4 unaff_EDI;
  
  pSVar2 = param_1;
  OrdnanceClass::OrdnanceClass
            ((OrdnanceClass *)this,(OrdnanceClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x6ba8d14a,&this->waveRadius,
                   pSVar2->waveRadius);
  if (this->waveRadius < 0.0001) {
    this->waveRadius = 0.0001;
  }
  fVar1 = 1.0 / this->waveRadius;
  this->waveRadiusInv = fVar1;
  this->waveRadiusExp = fVar1 * fVar1 * -2.5;
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x5ad61a27,&this->waveHeight,
                   pSVar2->waveHeight);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x971beda4,&this->startOffset,
                   pSVar2->startOffset);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x3a74c50d,&this->rampUpTime,
                   pSVar2->rampUpTime);
  this->rampUpRate = 1.0 / this->rampUpTime;
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x5ba4f6b0,&this->rampDownTime,
                   pSVar2->rampDownTime);
  this->rampDownRate = 1.0 / this->rampDownTime;
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0xad935b02,&this->sweepOmega,
                   pSVar2->sweepOmega);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0xbe57c368,&this->sweepVeloc,
                   pSVar2->sweepVeloc);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0xdee4f011,&this->shakeFrequency,
                   pSVar2->shakeFrequency);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0xce21ecf8,&this->shakeOmega,
                   pSVar2->shakeOmega);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0xf57df3d2,&this->shakeVeloc,
                   pSVar2->shakeVeloc);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x9ebf26a7,&this->walkerScale,
                   pSVar2->walkerScale);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x3b226d18,&this->towerScale,
                   pSVar2->towerScale);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x2fc331e2,&this->dampOmega,pSVar2->dampOmega)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x762c10d0,&this->levelOmega,
                   pSVar2->levelOmega);
  ParameterDB::Get((ParameterDB *)&param_1,0x7ff8e41b,0x2168f61,&this->buildingScale,
                   pSVar2->buildingScale);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
