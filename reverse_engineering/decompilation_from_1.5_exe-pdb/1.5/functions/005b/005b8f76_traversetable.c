/*
 * Entry: 005b8f76
 * Name: traversetable
 * Namespace: Global
 * Signature: int traversetable(global_State * param_1, Table * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl traversetable(global_State *param_1,Table *param_2)

{
  GCObject *pGVar1;
  Table *pTVar2;
  lua_TValue *plVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int extraout_EDX;
  undefined4 *extraout_EDX_00;
  undefined4 *puVar7;
  GCObject *unaff_ESI;
  int iVar8;
  bool bVar9;
  bool bVar10;
  
  pGVar1 = (GCObject *)(unaff_ESI->h).metatable;
  bVar10 = false;
  bVar9 = false;
  if ((pGVar1 != (GCObject *)0x0) && (((pGVar1->gch).marked & 3) != 0)) {
    reallymarkobject(param_1,pGVar1);
  }
  pTVar2 = (unaff_ESI->h).metatable;
  if ((((pTVar2 != (Table *)0x0) && ((pTVar2->flags & 8) == 0)) &&
      (plVar3 = luaT_gettm(pTVar2,TM_MODE,param_1->tmname[3]), plVar3 != (lua_TValue *)0x0)) &&
     (plVar3->tt == 4)) {
    pcVar4 = strchr((char *)((plVar3->value).b + 0x10),0x6b);
    bVar9 = pcVar4 != (char *)0x0;
    pcVar4 = strchr((char *)((plVar3->value).b + 0x10),0x76);
    bVar10 = pcVar4 != (char *)0x0;
    if ((bVar9) || (bVar10)) {
      (unaff_ESI->gch).marked = (bVar10 * '\x02' | bVar9) << 3 | (unaff_ESI->gch).marked & 0xe7;
      (unaff_ESI->h).gclist = param_1->weak;
      param_1->weak = unaff_ESI;
    }
    if (bVar9) {
      if (bVar10) {
        return 1;
      }
    }
    else if (bVar10) goto LAB_005b906f;
  }
  iVar8 = (unaff_ESI->h).sizearray;
  if (iVar8 != 0) {
    iVar5 = iVar8 << 4;
    do {
      iVar6 = iVar5 + -0x10;
      puVar7 = (undefined4 *)((int)&(unaff_ESI->h).array[-1].value + iVar5);
      iVar8 = iVar8 + -1;
      if ((3 < (int)puVar7[2]) && (pGVar1 = (GCObject *)*puVar7, ((pGVar1->gch).marked & 3) != 0)) {
        reallymarkobject(param_1,pGVar1);
        iVar6 = extraout_EDX;
      }
      iVar5 = iVar6;
    } while (iVar8 != 0);
  }
LAB_005b906f:
  iVar8 = 1 << ((unaff_ESI->h).lsizenode & 0x1f);
  if (iVar8 != 0) {
    iVar5 = iVar8 << 5;
    do {
      puVar7 = (undefined4 *)((int)&(unaff_ESI->h).node[-1].i_val.value + iVar5);
      iVar8 = iVar8 + -1;
      if (puVar7[2] == 0) {
        if (3 < (int)puVar7[6]) {
          puVar7[6] = 0xb;
        }
      }
      else {
        if (((!bVar9) && (3 < (int)puVar7[6])) && (((((GCObject *)puVar7[4])->gch).marked & 3) != 0)
           ) {
          reallymarkobject(param_1,(GCObject *)puVar7[4]);
          puVar7 = extraout_EDX_00;
        }
        if (((!bVar10) && (3 < (int)puVar7[2])) && (((((GCObject *)*puVar7)->gch).marked & 3) != 0))
        {
          reallymarkobject(param_1,(GCObject *)*puVar7);
        }
      }
      iVar5 = iVar5 + -0x20;
    } while (iVar8 != 0);
  }
  if ((!bVar9) && (!bVar10)) {
    return 0;
  }
  return 1;
}
