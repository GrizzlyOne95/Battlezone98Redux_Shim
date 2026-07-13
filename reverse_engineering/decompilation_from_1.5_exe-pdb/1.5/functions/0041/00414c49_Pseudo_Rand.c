/*
 * Entry: 00414c49
 * Name: Pseudo_Rand
 * Namespace: Global
 * Signature: float Pseudo_Rand(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Pseudo_Rand(void)

{
  Rand_Counter = Rand_Counter + 1U & 0xff;
  return Pseudo_Rand_Number[Rand_Counter];
}
