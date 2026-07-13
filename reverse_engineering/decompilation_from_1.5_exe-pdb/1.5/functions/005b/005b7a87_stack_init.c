/*
 * Entry: 005b7a87
 * Name: stack_init
 * Namespace: Global
 * Signature: void stack_init(lua_State * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl stack_init(lua_State *param_1,lua_State *param_2)

{
  void *pvVar1;
  int unaff_ESI;
  
  pvVar1 = luaM_realloc_(param_1,(void *)0x0,0,0xc0);
  *(void **)(unaff_ESI + 0x28) = pvVar1;
  *(void **)(unaff_ESI + 0x14) = pvVar1;
  *(undefined4 *)(unaff_ESI + 0x30) = 8;
  *(int *)(unaff_ESI + 0x24) = (int)pvVar1 + 0xa8;
  pvVar1 = luaM_realloc_(param_1,(void *)0x0,0,0x2d0);
  *(void **)(unaff_ESI + 8) = pvVar1;
  *(int *)(unaff_ESI + 0x1c) = (int)pvVar1 + 0x270;
  *(void **)(unaff_ESI + 0x20) = pvVar1;
  *(undefined4 *)(unaff_ESI + 0x2c) = 0x2d;
  *(void **)(*(int *)(unaff_ESI + 0x14) + 4) = pvVar1;
  *(undefined4 *)(*(int *)(unaff_ESI + 8) + 8) = 0;
  *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + 0x10;
  **(undefined4 **)(unaff_ESI + 0x14) = *(undefined4 *)(unaff_ESI + 8);
  *(undefined4 *)(unaff_ESI + 0xc) = **(undefined4 **)(unaff_ESI + 0x14);
  (*(undefined4 **)(unaff_ESI + 0x14))[2] = *(int *)(unaff_ESI + 8) + 0x140;
  return;
}
