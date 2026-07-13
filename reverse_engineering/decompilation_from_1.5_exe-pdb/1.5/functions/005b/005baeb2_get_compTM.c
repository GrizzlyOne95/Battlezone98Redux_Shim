/*
 * Entry: 005baeb2
 * Name: get_compTM
 * Namespace: Global
 * Signature: lua_TValue * get_compTM(lua_State * param_1, Table * param_2, Table * param_3, TMS param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl get_compTM(lua_State *param_1,Table *param_2,Table *param_3,TMS param_4)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  byte bVar4;
  int unaff_EBX;
  TMS unaff_EDI;
  
  if ((param_1 != (lua_State *)0x0) &&
     (bVar4 = (byte)(1 << ((byte)unaff_EDI & 0x1f)), (param_1->status & bVar4) == 0)) {
    iVar3 = unaff_EDI * 4 + 0xbc;
    plVar1 = luaT_gettm((Table *)param_1,unaff_EDI,*(TString **)(*(int *)(unaff_EBX + 0x10) + iVar3)
                       );
    if (plVar1 != (lua_TValue *)0x0) {
      if (param_1 == (lua_State *)param_2) {
        return plVar1;
      }
      if (((param_2 != (Table *)0x0) && ((param_2->flags & bVar4) == 0)) &&
         (plVar2 = luaT_gettm(param_2,unaff_EDI,*(TString **)(*(int *)(unaff_EBX + 0x10) + iVar3)),
         plVar2 != (lua_TValue *)0x0)) {
        iVar3 = luaO_rawequalObj(plVar1,plVar2);
        return (lua_TValue *)(-(uint)(iVar3 != 0) & (uint)plVar1);
      }
    }
  }
  return (lua_TValue *)0x0;
}
