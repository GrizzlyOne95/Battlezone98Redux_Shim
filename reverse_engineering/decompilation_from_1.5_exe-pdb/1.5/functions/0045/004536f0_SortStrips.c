/*
 * Entry: 004536f0
 * Name: SortStrips
 * Namespace: Global
 * Signature: void SortStrips(VECTOR_2D * param_1, int param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SortStrips(VECTOR_2D *param_1,int param_2,Strip **param_3)

{
  Strip **in_EAX;
  float *in_ECX;
  
  compareStart.x = *in_ECX;
  compareStart.z = in_ECX[1];
  std::_Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>
            (in_EAX,in_EAX + (int)((int)&param_1[-1].z + 3),
             (int)(in_EAX + (int)((int)&param_1[-1].z + 3)) - (int)in_EAX >> 2,CompareStrips);
  return;
}
