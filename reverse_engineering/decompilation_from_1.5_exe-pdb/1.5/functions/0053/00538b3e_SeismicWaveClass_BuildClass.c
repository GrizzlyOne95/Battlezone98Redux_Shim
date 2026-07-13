/*
 * Entry: 00538b3e
 * Name: SeismicWaveClass::BuildClass
 * Namespace: SeismicWaveClass
 * Signature: OrdnanceClass * BuildClass(SeismicWaveClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall SeismicWaveClass::BuildClass(SeismicWaveClass *this,long64 param_1)

{
  SeismicWaveClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0xc0);
  if (pSVar1 == (SeismicWaveClass *)0x0) {
    pSVar1 = (SeismicWaveClass *)0x0;
  }
  else {
    pSVar1 = SeismicWaveClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pSVar1;
}
