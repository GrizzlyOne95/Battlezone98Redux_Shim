/*
 * Entry: 00538cc8
 * Name: SeismicWaveClass::Build
 * Namespace: SeismicWaveClass
 * Signature: Ordnance * Build(SeismicWaveClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall SeismicWaveClass::Build(SeismicWaveClass *this,_OBJ76 *param_1)

{
  SeismicWave *pSVar1;
  
  pSVar1 = operator_new(0x108);
  if (pSVar1 == (SeismicWave *)0x0) {
    pSVar1 = (SeismicWave *)0x0;
  }
  else {
    pSVar1 = SeismicWave::SeismicWave(pSVar1,param_1,this);
  }
  return (Ordnance *)pSVar1;
}
