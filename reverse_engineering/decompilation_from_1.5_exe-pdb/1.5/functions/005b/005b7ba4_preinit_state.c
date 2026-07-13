/*
 * Entry: 005b7ba4
 * Name: preinit_state
 * Namespace: Global
 * Signature: void preinit_state(lua_State * param_1, global_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl preinit_state(lua_State *param_1,global_State *param_2)

{
  int in_EAX;
  undefined4 in_ECX;
  
  *(undefined4 *)(in_EAX + 0x10) = in_ECX;
  *(undefined4 *)(in_EAX + 0x20) = 0;
  *(undefined4 *)(in_EAX + 0x2c) = 0;
  *(undefined4 *)(in_EAX + 0x70) = 0;
  *(undefined4 *)(in_EAX + 0x44) = 0;
  *(undefined1 *)(in_EAX + 0x38) = 0;
  *(undefined4 *)(in_EAX + 0x3c) = 0;
  *(undefined1 *)(in_EAX + 0x39) = 1;
  *(undefined4 *)(in_EAX + 0x40) = 0;
  *(undefined4 *)(in_EAX + 0x68) = 0;
  *(undefined4 *)(in_EAX + 0x30) = 0;
  *(undefined2 *)(in_EAX + 0x36) = 0;
  *(undefined2 *)(in_EAX + 0x34) = 0;
  *(undefined1 *)(in_EAX + 6) = 0;
  *(undefined4 *)(in_EAX + 0x14) = 0;
  *(undefined4 *)(in_EAX + 0x28) = 0;
  *(undefined4 *)(in_EAX + 0x18) = 0;
  *(undefined4 *)(in_EAX + 0x74) = 0;
  *(undefined4 *)(in_EAX + 0x50) = 0;
  return;
}
