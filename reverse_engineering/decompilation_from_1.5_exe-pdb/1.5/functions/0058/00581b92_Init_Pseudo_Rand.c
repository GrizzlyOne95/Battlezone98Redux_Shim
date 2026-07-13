/*
 * Entry: 00581b92
 * Name: Init_Pseudo_Rand
 * Namespace: Global
 * Signature: void Init_Pseudo_Rand(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Pseudo_Rand(void)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  pfVar1 = Pseudo_Rand_Number;
  do {
    fVar2 = Random();
    fVar3 = Random();
    fVar4 = Random();
    fVar5 = Random();
    fVar6 = Random();
    *pfVar1 = (fVar6 + fVar5 + fVar4 + fVar3 + fVar2) * 0.2;
    pfVar1 = pfVar1 + 1;
  } while ((int)pfVar1 < 0xc90620);
  return;
}
