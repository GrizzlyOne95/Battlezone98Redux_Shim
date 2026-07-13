/*
 * Entry: 005c6086
 * Name: luaK_code
 * Namespace: Global
 * Signature: int luaK_code(FuncState * param_1, uint param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_code(FuncState *param_1,uint param_2,int param_3)

{
  int iVar1;
  void *pvVar2;
  int unaff_EBX;
  int *unaff_ESI;
  int unaff_EDI;
  
  iVar1 = *unaff_ESI;
  patchlistaux((FuncState *)unaff_ESI[6],0xff,unaff_ESI[6],unaff_EDI,unaff_EBX);
  unaff_ESI[8] = -1;
  if (*(int *)(iVar1 + 0x2c) < unaff_ESI[6] + 1) {
    pvVar2 = luaM_growaux_((lua_State *)unaff_ESI[4],*(void **)(iVar1 + 0xc),(int *)(iVar1 + 0x2c),4
                           ,0x7ffffffd,"code size overflow");
    *(void **)(iVar1 + 0xc) = pvVar2;
  }
  *(FuncState **)(*(int *)(iVar1 + 0xc) + unaff_ESI[6] * 4) = param_1;
  if (*(int *)(iVar1 + 0x30) < unaff_ESI[6] + 1) {
    pvVar2 = luaM_growaux_((lua_State *)unaff_ESI[4],*(void **)(iVar1 + 0x14),(int *)(iVar1 + 0x30),
                           4,0x7ffffffd,"code size overflow");
    *(void **)(iVar1 + 0x14) = pvVar2;
  }
  *(uint *)(*(int *)(iVar1 + 0x14) + unaff_ESI[6] * 4) = param_2;
  iVar1 = unaff_ESI[6];
  unaff_ESI[6] = iVar1 + 1;
  return iVar1;
}
