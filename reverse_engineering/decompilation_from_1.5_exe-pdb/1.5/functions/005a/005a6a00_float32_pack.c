/*
 * Entry: 005a6a00
 * Name: _float32_pack
 * Namespace: Global
 * Signature: long _float32_pack(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl _float32_pack(float param_1)

{
  int extraout_EAX;
  uint extraout_EAX_00;
  uint uVar1;
  float10 fVar2;
  float10 fVar3;
  double dVar4;
  
  uVar1 = 0;
  if (param_1 < 0.0) {
    param_1 = -param_1;
    uVar1 = 0x80000000;
  }
  fVar2 = (float10)__CIlog();
  fVar3 = (float10)__CIlog();
  floor((double)((float10)(double)fVar2 / fVar3 + (float10)0.001));
  _ftol2_sse();
  dVar4 = ldexp((double)param_1,0x14 - extraout_EAX);
  floor(dVar4 + 0.5);
  _ftol2_sse();
  return extraout_EAX_00 | (extraout_EAX + 0x300) * 0x200000 | uVar1;
}
