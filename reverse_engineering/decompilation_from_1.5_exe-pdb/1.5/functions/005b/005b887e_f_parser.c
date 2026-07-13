/*
 * Entry: 005b887e
 * Name: f_parser
 * Namespace: Global
 * Signature: void f_parser(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl f_parser(lua_State *param_1,void *param_2)

{
  lua_TValue *plVar1;
  lua_State *plVar2;
  int iVar3;
  code *pcVar4;
  global_State *pgVar5;
  GCObject *pGVar6;
  UpVal *pUVar7;
  
  plVar2 = param_1;
  iVar3 = luaZ_lookahead(*(Zio **)param_2);
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  pcVar4 = luaU_undump;
  if (iVar3 != 0x1b) {
    pcVar4 = luaY_parser;
  }
  pgVar5 = (global_State *)
           (*pcVar4)(param_1,*(undefined4 *)param_2,(int)param_2 + 4,
                     *(undefined4 *)((int)param_2 + 0x10));
  pGVar6 = (GCObject *)
           luaF_newLclosure(param_1,(uint)(byte)pgVar5->estimate,&((param_1->l_gt).value.gc)->h);
  param_1 = (lua_State *)0x0;
  (pGVar6->th).l_G = pgVar5;
  if ((uchar)pgVar5->estimate != '\0') {
    param_2 = &(pGVar6->h).lastfree;
    do {
      pUVar7 = luaF_newupval(plVar2);
      param_1 = (lua_State *)((int)&param_1->next + 1);
      *(UpVal **)param_2 = pUVar7;
      param_2 = (void *)((int)param_2 + 4);
    } while ((int)param_1 < (int)(uint)(byte)pgVar5->estimate);
  }
  plVar1 = plVar2->top;
  (plVar1->value).gc = pGVar6;
  plVar1->tt = 6;
  if ((int)plVar2->stack_last - (int)plVar2->top < 0x11) {
    luaD_growstack(plVar2,1);
  }
  plVar2->top = plVar2->top + 1;
  return;
}
