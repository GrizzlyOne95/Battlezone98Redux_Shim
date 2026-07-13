/*
 * Entry: 004ecbac
 * Name: get_weapon_quad
 * Namespace: Global
 * Signature: int get_weapon_quad(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl get_weapon_quad(float param_1,float param_2)

{
  uint extraout_EAX;
  
  floor((double)(((param_2 - param_1) + 6.6758842) * 1.2732395));
  _ftol2_sse();
  return extraout_EAX & 7;
}
