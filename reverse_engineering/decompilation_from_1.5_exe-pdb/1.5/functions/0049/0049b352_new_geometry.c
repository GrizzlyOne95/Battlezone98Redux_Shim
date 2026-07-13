/*
 * Entry: 0049b352
 * Name: new_geometry
 * Namespace: Global
 * Signature: _GEOMETRY * new_geometry(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_GEOMETRY * __cdecl new_geometry(long param_1,long param_2,long param_3)

{
  int in_EAX;
  _GEOMETRY *p_Var1;
  int in_ECX;
  uint uVar2;
  
  uVar2 = (in_EAX + in_ECX * 4) * 0x10 + (param_1 + 1) * 0x18;
  p_Var1 = operator_new__(uVar2);
  memset(p_Var1,0,uVar2);
  return p_Var1;
}
