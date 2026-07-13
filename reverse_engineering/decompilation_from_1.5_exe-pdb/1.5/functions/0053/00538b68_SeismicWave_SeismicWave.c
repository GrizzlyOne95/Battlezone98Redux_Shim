/*
 * Entry: 00538b68
 * Name: SeismicWave::SeismicWave
 * Namespace: SeismicWave
 * Signature: SeismicWave * SeismicWave(SeismicWave * this, _OBJ76 * param_1, SeismicWaveClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SeismicWave * __thiscall
SeismicWave::SeismicWave(SeismicWave *this,_OBJ76 *param_1,SeismicWaveClass *param_2)

{
  longlong lVar1;
  short *psVar2;
  uint uVar3;
  int unaff_EDI;
  int local_c;
  
  Ordnance::Ordnance((Ordnance *)this,param_1,(OrdnanceClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  Set_Rounding(unaff_EDI);
  local_c = SUB84((double)((param_2->waveRadius + param_2->waveRadius) * 0.1 + (float)Float2Int),0);
  Set_Rounding(unaff_EDI);
  uVar3 = (local_c + 2) * (local_c + 2);
  lVar1 = (ulonglong)uVar3 * 2;
  psVar2 = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  this->deltaH = psVar2;
  memset(psVar2,0,uVar3 * 2);
  (param_1->bSphere).radius = param_2->waveRadius;
  return this;
}
