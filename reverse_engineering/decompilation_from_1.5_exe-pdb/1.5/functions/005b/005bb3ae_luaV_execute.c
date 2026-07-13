/*
 * Entry: 005bb3ae
 * Name: luaV_execute
 * Namespace: Global
 * Signature: void luaV_execute(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaV_execute(lua_State *param_1,int param_2)

{
  int *piVar1;
  double dVar2;
  Table *pTVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  global_State *pgVar8;
  uint *puVar9;
  double dVar10;
  lua_State *plVar11;
  int iVar12;
  Value *pVVar13;
  Value *pVVar14;
  int iVar15;
  lua_TValue *plVar16;
  uint uVar17;
  UpVal *pUVar18;
  CallInfo *pCVar19;
  undefined4 *puVar20;
  lua_State *plVar21;
  lua_TValue *unaff_EBX;
  lua_TValue *unaff_ESI;
  lua_State *unaff_EDI;
  lua_TValue *plVar22;
  lua_TValue *plVar23;
  UpVal **ppUVar24;
  GCObject *pGVar25;
  float10 fVar26;
  Value *pVVar27;
  char *pcVar28;
  Value local_48;
  undefined4 local_40;
  Value local_38;
  undefined4 local_30;
  undefined8 local_28;
  undefined8 local_20;
  GCObject *local_18;
  Value *local_14;
  int local_10;
  int local_c;
  lua_TValue *local_8;
  
  plVar11 = param_1;
LAB_005bb3ba:
  local_8 = plVar11->base;
  local_10 = (plVar11->ci->func->value).b;
  local_c = *(int *)(*(int *)(local_10 + 0x10) + 8);
  plVar21 = (lua_State *)plVar11->savedpc;
switchD_005bb43a_default:
  param_1 = plVar21;
  pGVar25 = param_1->next;
  plVar21 = (lua_State *)&param_1->tt;
  if ((plVar11->hookmask & 0xc) != 0) {
    piVar1 = &plVar11->hookcount;
    *piVar1 = *piVar1 + -1;
    if ((*piVar1 == 0) || ((plVar11->hookmask & 4) != 0)) {
      traceexec(plVar21,(uint *)unaff_EDI);
      if (plVar11->status == '\x01') {
        plVar11->savedpc = (uint *)param_1;
        return;
      }
      local_8 = plVar11->base;
    }
  }
  local_14 = (Value *)((uint)pGVar25 >> 6 & 0xff);
  iVar12 = (int)local_14 * 0x10;
  pVVar14 = &local_8[(int)local_14].value;
  local_20._4_4_ = iVar12;
  switch((uint)pGVar25 & 0x3f) {
  case 0:
    plVar16 = local_8 + ((uint)pGVar25 >> 0x17);
    goto LAB_005bb44a;
  case 1:
    plVar16 = (lua_TValue *)(((uint)pGVar25 >> 0xe) * 0x10 + local_c);
LAB_005bb44a:
    pVVar14->gc = (plVar16->value).gc;
    *(undefined4 *)((int)pVVar14 + 4) = *(undefined4 *)((int)&plVar16->value + 4);
    iVar12 = plVar16->tt;
    goto LAB_005bb457;
  case 2:
    pVVar14->b = (uint)pGVar25 >> 0x17;
    pVVar14[1].b = 1;
    if (((uint)pGVar25 & 0x7fc000) != 0) goto LAB_005bbbbf;
    goto switchD_005bb43a_default;
  case 3:
    pVVar13 = &local_8[(uint)pGVar25 >> 0x17].value;
    do {
      pVVar13[1].gc = (GCObject *)0x0;
      pVVar13 = pVVar13 + -2;
    } while (pVVar14 <= pVVar13);
    goto switchD_005bb43a_default;
  case 4:
    puVar20 = *(undefined4 **)(*(int *)(local_10 + 0x14 + ((uint)pGVar25 >> 0x17) * 4) + 8);
    pVVar14->gc = (GCObject *)*puVar20;
    *(undefined4 *)((int)pVVar14 + 4) = puVar20[1];
    iVar12 = puVar20[2];
    goto LAB_005bb457;
  case 5:
    local_38.gc = (GCObject *)*(undefined4 *)(local_10 + 0xc);
    plVar16 = (lua_TValue *)(((uint)pGVar25 >> 0xe) * 0x10 + local_c);
    plVar11->savedpc = (uint *)plVar21;
    local_30 = 5;
    pVVar13 = &local_38;
    goto LAB_005bb666;
  case 6:
    plVar11->savedpc = (uint *)plVar21;
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    pVVar13 = &local_8[(uint)pGVar25 >> 0x17].value;
    goto LAB_005bb666;
  case 7:
    local_48.gc = (GCObject *)*(undefined4 *)(local_10 + 0xc);
    plVar16 = (lua_TValue *)(((uint)pGVar25 >> 0xe) * 0x10 + local_c);
    plVar11->savedpc = (uint *)plVar21;
    local_40 = 5;
    pVVar27 = &local_48;
    pVVar13 = pVVar14;
    goto LAB_005bb5dd;
  case 8:
    pGVar25 = *(GCObject **)(local_10 + 0x14 + ((uint)pGVar25 >> 0x17) * 4);
    pTVar3 = (pGVar25->h).metatable;
    pTVar3->next = pVVar14->gc;
    uVar4 = *(undefined4 *)((int)pVVar14 + 4);
    pTVar3->tt = (char)uVar4;
    pTVar3->marked = (char)((uint)uVar4 >> 8);
    pTVar3->flags = (char)((uint)uVar4 >> 0x10);
    pTVar3->lsizenode = (char)((uint)uVar4 >> 0x18);
    pTVar3->metatable = (Table *)pVVar14[1].gc;
    if (((3 < pVVar14[1].b) && (((pVVar14->gc->gch).marked & 3) != 0)) &&
       (((pGVar25->gch).marked & 4) != 0)) {
      luaC_barrierf(plVar11,pGVar25,pVVar14->gc);
    }
    goto switchD_005bb43a_default;
  case 9:
    plVar11->savedpc = (uint *)plVar21;
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      pVVar13 = &local_8[uVar17 & 0x1ff].value;
    }
    else {
      pVVar13 = (Value *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0x17;
    pVVar27 = pVVar14;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
LAB_005bb5dd:
    luaV_settable(plVar11,(lua_TValue *)pVVar27,plVar16,(lua_TValue *)pVVar13);
    param_1 = plVar21;
    break;
  case 10:
    iVar12 = luaO_fb2int((uint)pGVar25 >> 0xe & 0x1ff);
    iVar15 = luaO_fb2int((uint)pGVar25 >> 0x17);
    pGVar25 = (GCObject *)luaH_new(plVar11,iVar15,iVar12);
    pVVar14->gc = pGVar25;
    pVVar14[1].b = 5;
    param_1 = plVar21;
    goto LAB_005bbf21;
  case 0xb:
    pVVar13 = &local_8[(uint)pGVar25 >> 0x17].value;
    uVar17 = (uint)pGVar25 >> 0xe;
    pVVar14[2].gc = pVVar13->gc;
    *(undefined4 *)((int)pVVar14 + 0x14) = *(undefined4 *)((int)pVVar13 + 4);
    pVVar14[3].gc = pVVar13[1].gc;
    plVar11->savedpc = (uint *)plVar21;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
LAB_005bb666:
    luaV_gettable(plVar11,(lua_TValue *)pVVar13,plVar16,(lua_TValue *)pVVar14);
    param_1 = plVar21;
    break;
  case 0xc:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar22 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar22 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    if ((plVar16->tt != 3) || (plVar22->tt != 3)) {
      plVar23 = (lua_TValue *)0x5;
      goto LAB_005bb7e7;
    }
    dVar2 = (plVar22->value).n + (plVar16->value).n;
LAB_005bb6c4:
    pVVar14->n = dVar2;
    pVVar14[1].b = 3;
    goto switchD_005bb43a_default;
  case 0xd:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar22 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar22 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    if ((plVar16->tt == 3) && (plVar22->tt == 3)) {
      dVar2 = (plVar16->value).n - (plVar22->value).n;
      goto LAB_005bb6c4;
    }
    plVar23 = (lua_TValue *)0x6;
    goto LAB_005bb7e7;
  case 0xe:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar22 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar22 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    if ((plVar16->tt == 3) && (plVar22->tt == 3)) {
      dVar2 = (plVar22->value).n * (plVar16->value).n;
      goto LAB_005bb6c4;
    }
    plVar23 = (lua_TValue *)0x7;
    goto LAB_005bb7e7;
  case 0xf:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar22 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar22 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    if ((plVar16->tt == 3) && (plVar22->tt == 3)) {
      dVar2 = (plVar16->value).n / (plVar22->value).n;
      goto LAB_005bb6c4;
    }
    plVar23 = (lua_TValue *)0x8;
LAB_005bb7e7:
    plVar11->savedpc = (uint *)plVar21;
LAB_005bb902:
    Arith(plVar11,plVar16,plVar22,plVar23,(TMS)unaff_EDI);
    param_1 = plVar21;
    break;
  case 0x10:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar22 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar22 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    if ((plVar16->tt == 3) && (plVar22->tt == 3)) {
      local_20 = plVar16->value;
      local_28 = plVar22->value;
      fVar26 = (float10)floor();
      fVar26 = (float10)local_20 - fVar26 * (float10)local_28;
      goto LAB_005bb866;
    }
    plVar23 = (lua_TValue *)0x9;
LAB_005bb8d2:
    plVar11->savedpc = (uint *)plVar21;
    goto LAB_005bb902;
  case 0x11:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar22 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar22 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    if ((plVar16->tt != 3) || (plVar22->tt != 3)) {
      plVar23 = (lua_TValue *)0xa;
      goto LAB_005bb8d2;
    }
    fVar26 = (float10)__CIpow();
LAB_005bb866:
    pVVar14->n = (double)fVar26;
    pVVar14[1].b = 3;
    goto switchD_005bb43a_default;
  case 0x12:
    plVar16 = local_8 + ((uint)pGVar25 >> 0x17);
    iVar12 = 3;
    if (plVar16->tt != 3) {
      plVar23 = (lua_TValue *)0xb;
      plVar11->savedpc = (uint *)plVar21;
      plVar22 = plVar16;
      goto LAB_005bb902;
    }
    pVVar14->n = -(plVar16->value).n;
LAB_005bb457:
    pVVar14[1].b = iVar12;
    goto switchD_005bb43a_default;
  case 0x13:
    iVar12 = local_8[(uint)pGVar25 >> 0x17].tt;
    if ((iVar12 == 0) ||
       ((iVar12 == 1 && (local_8[(uint)pGVar25 >> 0x17].value.gc == (GCObject *)0x0)))) {
      pGVar25 = (GCObject *)0x1;
    }
    else {
      pGVar25 = (GCObject *)0x0;
    }
    pVVar14->gc = pGVar25;
    pVVar14[1].b = 1;
    goto switchD_005bb43a_default;
  case 0x14:
    plVar16 = local_8 + ((uint)pGVar25 >> 0x17);
    if (plVar16->tt == 4) {
      local_28._4_4_ = *(int *)((plVar16->value).b + 0xc);
      dVar2 = (double)(int)local_28._4_4_;
      if ((int)local_28._4_4_ < 0) {
        dVar2 = dVar2 + 4294967296.0;
      }
    }
    else {
      if (plVar16->tt != 5) {
        plVar11->savedpc = (uint *)plVar21;
        iVar12 = call_binTM(plVar11,plVar16,&luaO_nilobject_,(lua_TValue *)pVVar14,TM_LEN);
        param_1 = plVar21;
        if (iVar12 == 0) {
          luaG_typeerror(plVar11,plVar16,"get length of");
        }
        break;
      }
      iVar12 = luaH_getn(&((plVar16->value).gc)->h);
      local_20._4_4_ = iVar12;
      dVar2 = (double)iVar12;
    }
    pVVar14->n = dVar2;
    pVVar14[1].b = 3;
    goto switchD_005bb43a_default;
  case 0x15:
    uVar17 = (uint)pGVar25 >> 0xe & 0x1ff;
    plVar11->savedpc = (uint *)plVar21;
    luaV_concat(plVar11,(uVar17 - ((uint)pGVar25 >> 0x17)) + 1,uVar17);
    if (plVar11->l_G->GCthreshold <= plVar11->l_G->totalbytes) {
      luaC_step(plVar11);
    }
    local_8 = plVar11->base;
    plVar16 = local_8 + ((uint)pGVar25 >> 0x17);
    puVar20 = (undefined4 *)((int)&local_8->value + local_20._4_4_);
    *puVar20 = (plVar16->value).gc;
    puVar20[1] = *(undefined4 *)((int)&plVar16->value + 4);
    puVar20[2] = plVar16->tt;
    goto switchD_005bb43a_default;
  case 0x16:
    goto switchD_005bb43a_caseD_16;
  case 0x17:
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + uVar17;
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar23 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar23 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    plVar11->savedpc = (uint *)plVar21;
    if ((plVar16->tt == plVar23->tt) &&
       (iVar12 = luaV_equalval(plVar11,plVar16,plVar23), iVar12 != 0)) {
      pVVar14 = (Value *)0x1;
    }
    else {
      pVVar14 = (Value *)0x0;
    }
    goto LAB_005bbb24;
  case 0x18:
    plVar11->savedpc = (uint *)plVar21;
    uVar17 = (uint)pGVar25 >> 0xe;
    if ((uVar17 & 0x100) == 0) {
      plVar16 = local_8 + (uVar17 & 0x1ff);
    }
    else {
      plVar16 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    uVar17 = (uint)pGVar25 >> 0x17;
    if ((uVar17 & 0x100) == 0) {
      plVar23 = local_8 + uVar17;
    }
    else {
      plVar23 = (lua_TValue *)((uVar17 & 0xff) * 0x10 + local_c);
    }
    pVVar14 = (Value *)luaV_lessthan(plVar11,plVar23,plVar16);
    goto LAB_005bbb24;
  case 0x19:
    plVar11->savedpc = (uint *)plVar21;
    pVVar14 = (Value *)lessequal(unaff_EDI,unaff_ESI,unaff_EBX);
LAB_005bbb24:
    if (pVVar14 == local_14) {
      uVar5._0_1_ = param_1->tt;
      uVar5._1_1_ = param_1->marked;
      uVar5._2_1_ = param_1->status;
      uVar5._3_1_ = param_1->field_0x7;
      plVar21 = (lua_State *)(&param_1[-0x1111].next + (uVar5 >> 0xe));
    }
    param_1 = plVar21;
    local_8 = plVar11->base;
    plVar21 = param_1;
LAB_005bbdcc:
    param_1 = plVar21;
    plVar21 = (lua_State *)&param_1->tt;
    goto switchD_005bb43a_default;
  case 0x1a:
    if ((pVVar14[1].gc == (GCObject *)0x0) ||
       ((pVVar14[1].gc == (GCObject *)0x1 && (pVVar14->gc == (GCObject *)0x0)))) {
      uVar17 = 1;
    }
    else {
      uVar17 = 0;
    }
    if (uVar17 != ((uint)pGVar25 >> 0xe & 0x1ff)) {
LAB_005bbbad:
      uVar6._0_1_ = param_1->tt;
      uVar6._1_1_ = param_1->marked;
      uVar6._2_1_ = param_1->status;
      uVar6._3_1_ = param_1->field_0x7;
      plVar21 = (lua_State *)(&param_1[-0x1111].next + (uVar6 >> 0xe));
    }
    goto LAB_005bbbbf;
  case 0x1b:
    plVar16 = local_8 + ((uint)pGVar25 >> 0x17);
    if ((plVar16->tt == 0) || ((plVar16->tt == 1 && ((plVar16->value).gc == (GCObject *)0x0)))) {
      uVar17 = 1;
    }
    else {
      uVar17 = 0;
    }
    if (uVar17 != ((uint)pGVar25 >> 0xe & 0x1ff)) {
      pVVar14->gc = (plVar16->value).gc;
      *(undefined4 *)((int)pVVar14 + 4) = *(undefined4 *)((int)&plVar16->value + 4);
      pVVar14[1].gc = (GCObject *)plVar16->tt;
      goto LAB_005bbbad;
    }
LAB_005bbbbf:
    param_1 = plVar21;
    plVar21 = (lua_State *)&param_1->tt;
    goto switchD_005bb43a_default;
  case 0x1c:
    iVar12 = ((uint)pGVar25 >> 0xe & 0x1ff) - 1;
    if ((uint)pGVar25 >> 0x17 != 0) {
      plVar11->top = (lua_TValue *)(pVVar14 + ((uint)pGVar25 >> 0x17) * 2);
    }
    plVar11->savedpc = (uint *)plVar21;
    iVar15 = luaD_precall(plVar11,(lua_TValue *)pVVar14,iVar12);
    if (iVar15 == 0) {
      param_2 = param_2 + 1;
      goto LAB_005bb3ba;
    }
    if (iVar15 != 1) {
      return;
    }
    param_1 = plVar21;
    if (-1 < iVar12) {
      plVar11->top = plVar11->ci->top;
    }
    break;
  case 0x1d:
    if ((uint)pGVar25 >> 0x17 != 0) {
      plVar11->top = (lua_TValue *)(pVVar14 + ((uint)pGVar25 >> 0x17) * 2);
    }
    plVar11->savedpc = (uint *)plVar21;
    iVar12 = luaD_precall(plVar11,(lua_TValue *)pVVar14,-1);
    if (iVar12 == 0) {
      pCVar19 = plVar11->ci;
      plVar16 = pCVar19->func;
      local_20._4_4_ = pCVar19[-1].func;
      if (plVar11->openupval != (GCObject *)0x0) {
        luaF_close(plVar11,pCVar19[-1].base);
      }
      pCVar19[-1].base = pCVar19[-1].func + ((int)pCVar19->base - (int)plVar16 >> 4);
      plVar21 = (lua_State *)0x0;
      plVar11->base = pCVar19[-1].func + ((int)pCVar19->base - (int)plVar16 >> 4);
      param_1 = (lua_State *)0x0;
      if (plVar16 < plVar11->top) {
        iVar12 = 0;
        plVar23 = plVar16;
        do {
          puVar20 = (undefined4 *)(iVar12 + local_20._4_4_);
          *puVar20 = (plVar23->value).gc;
          puVar20[1] = *(undefined4 *)((int)&plVar23->value + 4);
          puVar20[2] = plVar23->tt;
          plVar21 = (lua_State *)((int)&param_1->next + 1);
          iVar12 = (int)plVar21 * 0x10;
          plVar23 = plVar16 + (int)plVar21;
          param_1 = plVar21;
        } while (plVar23 < plVar11->top);
      }
      plVar16 = (lua_TValue *)((int)plVar21 * 0x10 + local_20._4_4_);
      plVar11->top = plVar16;
      pCVar19[-1].top = plVar16;
      puVar9 = plVar11->savedpc;
      pCVar19[-1].tailcalls = pCVar19[-1].tailcalls + 1;
      pCVar19[-1].savedpc = puVar9;
      plVar11->ci = plVar11->ci + -1;
      goto LAB_005bb3ba;
    }
    param_1 = plVar21;
    if (iVar12 != 1) {
      return;
    }
    break;
  case 0x1e:
    goto switchD_005bb43a_caseD_1e;
  case 0x1f:
    dVar10 = pVVar14[4].n + pVVar14->n;
    dVar2 = pVVar14[2].n;
    if (pVVar14[4].n <= 0.0) {
      if (dVar10 < dVar2) goto switchD_005bb43a_default;
    }
    else if (dVar10 < dVar2 == (dVar10 == dVar2)) goto switchD_005bb43a_default;
    pVVar14->n = dVar10;
    pVVar14[1].b = 3;
    pVVar14[6].n = dVar10;
    pVVar14[7].b = 3;
    plVar21 = (lua_State *)(&param_1[-0x1111].next + ((uint)pGVar25 >> 0xe));
    goto switchD_005bb43a_default;
  case 0x20:
    local_14 = pVVar14 + 4;
    plVar11->savedpc = (uint *)plVar21;
    if ((pVVar14[1].gc == (GCObject *)0x3) ||
       (plVar16 = luaV_tonumber((lua_TValue *)pVVar14,(lua_TValue *)pVVar14),
       plVar16 != (lua_TValue *)0x0)) {
      if ((pVVar14[3].gc != (GCObject *)0x3) &&
         (plVar16 = luaV_tonumber((lua_TValue *)(pVVar14 + 2),(lua_TValue *)(pVVar14 + 2)),
         plVar16 == (lua_TValue *)0x0)) {
        pcVar28 = "\'for\' limit must be a number";
        goto LAB_005bbd05;
      }
      if ((local_14[1].gc != (GCObject *)0x3) &&
         (local_14 = &luaV_tonumber((lua_TValue *)local_14,(lua_TValue *)local_14)->value,
         local_14 == (Value *)0x0)) {
        pcVar28 = "\'for\' step must be a number";
        goto LAB_005bbd05;
      }
    }
    else {
      pcVar28 = "\'for\' initial value must be a number";
LAB_005bbd05:
      luaG_runerror(plVar11,pcVar28);
    }
    dVar2 = local_14->n;
    pVVar14[1].b = 3;
    pVVar14->n = pVVar14->n - dVar2;
switchD_005bb43a_caseD_16:
    plVar21 = (lua_State *)(&param_1[-0x1111].next + ((uint)pGVar25 >> 0xe));
    goto switchD_005bb43a_default;
  case 0x21:
    pVVar14[10].gc = pVVar14[4].gc;
    *(undefined4 *)((int)pVVar14 + 0x54) = *(undefined4 *)((int)pVVar14 + 0x24);
    pVVar14[0xb].gc = pVVar14[5].gc;
    pVVar14[8].gc = pVVar14[2].gc;
    *(undefined4 *)((int)pVVar14 + 0x44) = *(undefined4 *)((int)pVVar14 + 0x14);
    pVVar14[9].gc = pVVar14[3].gc;
    pVVar14[6].gc = pVVar14->gc;
    *(undefined4 *)((int)pVVar14 + 0x34) = *(undefined4 *)((int)pVVar14 + 4);
    pVVar14[7].gc = pVVar14[1].gc;
    plVar11->top = (lua_TValue *)(pVVar14 + 0xc);
    plVar11->savedpc = (uint *)plVar21;
    luaD_call(plVar11,(lua_TValue *)(pVVar14 + 6),(uint)pGVar25 >> 0xe & 0x1ff);
    local_8 = plVar11->base;
    plVar11->top = plVar11->ci->top;
    plVar16 = local_8 + (int)((int)local_14 + 3);
    if (plVar16->tt != 0) {
      plVar16[-1].value.gc = (plVar16->value).gc;
      *(undefined4 *)((int)&plVar16[-1].value + 4) = *(undefined4 *)((int)&plVar16->value + 4);
      plVar16[-1].tt = plVar16->tt;
      uVar7._0_1_ = param_1->tt;
      uVar7._1_1_ = param_1->marked;
      uVar7._2_1_ = param_1->status;
      uVar7._3_1_ = param_1->field_0x7;
      plVar21 = (lua_State *)(&param_1[-0x1111].next + (uVar7 >> 0xe));
    }
    goto LAB_005bbdcc;
  case 0x22:
    local_14 = (Value *)((uint)pGVar25 >> 0x17);
    uVar17 = (uint)pGVar25 >> 0xe & 0x1ff;
    if (local_14 == (Value *)0x0) {
      local_14 = (Value *)(((int)plVar11->top - (int)pVVar14 >> 4) + -1);
      plVar11->top = plVar11->ci->top;
    }
    if (uVar17 == 0) {
      uVar17._0_1_ = param_1->tt;
      uVar17._1_1_ = param_1->marked;
      uVar17._2_1_ = param_1->status;
      uVar17._3_1_ = param_1->field_0x7;
      plVar21 = (lua_State *)&param_1->top;
    }
    param_1 = plVar21;
    plVar21 = param_1;
    if (pVVar14[1].gc == (GCObject *)0x5) {
      local_20._4_4_ = pVVar14->gc;
      local_18 = (GCObject *)(uVar17 * 0x32 + -0x32 + (int)local_14);
      if (((Table *)local_20._4_4_)->sizearray < (int)local_18) {
        luaH_resizearray(plVar11,(Table *)local_20._4_4_,(int)local_18);
      }
      if (0 < (int)local_14) {
        pVVar14 = pVVar14 + (int)local_14 * 2;
        do {
          pTVar3 = (Table *)local_20._4_4_;
          plVar16 = luaH_setnum(plVar11,(Table *)local_20._4_4_,(int)local_18);
          (plVar16->value).gc = pVVar14->gc;
          *(int *)((int)&plVar16->value + 4) = *(int *)((int)pVVar14 + 4);
          local_18 = (GCObject *)((int)local_18 + -1);
          plVar16->tt = (int)pVVar14[1].gc;
          if (((3 < pVVar14[1].b) && ((*(byte *)(pVVar14->b + 5) & 3) != 0)) &&
             ((pTVar3->marked & 4) != 0)) {
            luaC_barrierback(plVar11,pTVar3);
          }
          local_14 = (Value *)((int)local_14 + -1);
          pVVar14 = pVVar14 + -2;
        } while (0 < (int)local_14);
      }
    }
    goto switchD_005bb43a_default;
  case 0x23:
    luaF_close(plVar11,(lua_TValue *)pVVar14);
    goto switchD_005bb43a_default;
  case 0x24:
    pgVar8 = *(global_State **)
              (*(int *)(*(int *)(local_10 + 0x10) + 0x10) + ((uint)pGVar25 >> 0xe) * 4);
    local_20._4_1_ = (undefined1)pgVar8->estimate;
    local_20._5_3_ = 0;
    pGVar25 = (GCObject *)
              luaF_newLclosure(plVar11,(uint)(byte)local_20._4_1_,*(Table **)(local_10 + 0xc));
    (pGVar25->th).l_G = pgVar8;
    param_1 = plVar21;
    local_18 = pGVar25;
    if (0 < (int)local_20._4_4_) {
      ppUVar24 = (UpVal **)&(pGVar25->h).lastfree;
      do {
        uVar17 = (uint)param_1->next >> 0x17;
        if (((byte)param_1->next & 0x3f) == 4) {
          pUVar18 = *(UpVal **)(local_10 + 0x14 + uVar17 * 4);
        }
        else {
          pUVar18 = luaF_findupval(plVar11,local_8 + uVar17);
          pGVar25 = local_18;
        }
        param_1 = (lua_State *)&param_1->tt;
        *ppUVar24 = pUVar18;
        ppUVar24 = ppUVar24 + 1;
        iVar12 = local_20._4_4_ + -1;
        local_20._4_4_ = iVar12;
      } while (iVar12 != 0);
    }
    pVVar14->gc = pGVar25;
    pVVar14[1].b = 6;
LAB_005bbf21:
    plVar11->savedpc = (uint *)param_1;
    if (plVar11->l_G->GCthreshold <= plVar11->l_G->totalbytes) {
      luaC_step(plVar11);
    }
    break;
  case 0x25:
    pCVar19 = plVar11->ci;
    local_18 = (GCObject *)(((uint)pGVar25 >> 0x17) - 1);
    local_28._4_4_ = pCVar19;
    pGVar25 = (GCObject *)
              ((((int)pCVar19->base - (int)pCVar19->func >> 4) -
               (uint)*(byte *)(*(int *)(local_10 + 0x10) + 0x49)) + -1);
    if (local_18 == (GCObject *)0xffffffff) {
      plVar11->savedpc = (uint *)plVar21;
      local_14 = (Value *)((int)pGVar25 * 0x10);
      if ((int)plVar11->stack_last - (int)plVar11->top <= (int)local_14) {
        luaD_growstack(plVar11,(int)pGVar25);
        iVar12 = local_20._4_4_;
        pCVar19 = (CallInfo *)local_28._4_4_;
      }
      local_8 = plVar11->base;
      pVVar14 = (Value *)((int)&local_8->value + iVar12);
      plVar11->top = (lua_TValue *)((int)pVVar14 + (int)local_14);
      local_18 = pGVar25;
    }
    local_14 = (Value *)0x0;
    if (0 < (int)local_18) {
      local_20._4_4_ = (int)pGVar25 * -0x10;
      pVVar14 = pVVar14 + 1;
      do {
        if ((int)local_14 < (int)pGVar25) {
          puVar20 = (undefined4 *)((int)&pCVar19->base->value + local_20._4_4_);
          (((lua_TValue *)(&pVVar14->gc + -2))->value).gc = (GCObject *)*puVar20;
          (&pVVar14->gc)[-1] = (GCObject *)puVar20[1];
          pVVar14->gc = (GCObject *)puVar20[2];
        }
        else {
          pVVar14->gc = (GCObject *)0x0;
        }
        local_14 = (Value *)((int)local_14 + 1);
        local_20._4_4_ = local_20._4_4_ + 0x10;
        pVVar14 = (Value *)(&pVVar14->gc + 4);
      } while ((int)local_14 < (int)local_18);
    }
  default:
    goto switchD_005bb43a_default;
  }
  local_8 = plVar11->base;
  plVar21 = param_1;
  goto switchD_005bb43a_default;
switchD_005bb43a_caseD_1e:
  if ((uint)pGVar25 >> 0x17 != 0) {
    plVar11->top = (lua_TValue *)(pVVar14 + (((uint)pGVar25 >> 0x17) - 1) * 2);
  }
  if (plVar11->openupval != (GCObject *)0x0) {
    luaF_close(plVar11,local_8);
  }
  plVar11->savedpc = (uint *)plVar21;
  iVar12 = luaD_poscall(plVar11,(lua_TValue *)pVVar14);
  param_2 = param_2 + -1;
  if (param_2 == 0) {
    return;
  }
  if (iVar12 != 0) {
    plVar11->top = plVar11->ci->top;
  }
  goto LAB_005bb3ba;
}
