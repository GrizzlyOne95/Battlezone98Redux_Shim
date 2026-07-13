/*
 * Entry: 005b5c09
 * Name: getcurrenv
 * Namespace: Global
 * Signature: Table * getcurrenv(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Table * __cdecl getcurrenv(lua_State *param_1)

{
  int in_EAX;
  
  if (*(int *)(in_EAX + 0x14) == *(int *)(in_EAX + 0x28)) {
    return *(Table **)(in_EAX + 0x48);
  }
  return *(Table **)(**(int **)(*(int *)(in_EAX + 0x14) + 4) + 0xc);
}
