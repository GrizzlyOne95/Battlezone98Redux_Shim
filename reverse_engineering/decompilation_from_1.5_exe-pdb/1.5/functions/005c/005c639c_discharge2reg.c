/*
 * Entry: 005c639c
 * Name: discharge2reg
 * Namespace: Global
 * Signature: void discharge2reg(FuncState * param_1, expdesc * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl discharge2reg(FuncState *param_1,expdesc *param_2,int param_3)

{
  uint *puVar1;
  expkind eVar2;
  uint uVar3;
  uint unaff_EBX;
  expdesc *unaff_ESI;
  FuncState *unaff_EDI;
  undefined4 unaff_retaddr;
  OpCode OVar4;
  
  luaK_dischargevars(unaff_EDI,unaff_ESI);
  eVar2 = unaff_ESI->k;
  if (eVar2 == VNIL) {
    luaK_nil(unaff_EDI,unaff_EBX,1);
    goto LAB_005c6451;
  }
  if ((int)eVar2 < 2) {
    return;
  }
  if ((int)eVar2 < 4) {
    uVar3 = (uint)(eVar2 == VTRUE);
    OVar4 = OP_LOADBOOL;
  }
  else {
    if (eVar2 == VK) {
      luaK_codeABx(unaff_EDI,OP_LOADK,unaff_EBX,(unaff_ESI->u).s.info);
      goto LAB_005c6451;
    }
    if (eVar2 == VKNUM) {
      uVar3 = luaK_numberK(unaff_EDI,(double)CONCAT44(unaff_retaddr,(unaff_ESI->u).s.aux));
      luaK_codeABx(unaff_EDI,OP_LOADK,unaff_EBX,uVar3);
      goto LAB_005c6451;
    }
    if (eVar2 == VRELOCABLE) {
      puVar1 = unaff_EDI->f->code + (unaff_ESI->u).s.info;
      *puVar1 = *puVar1 ^ (unaff_EBX << 6 ^ *puVar1) & 0x3fc0;
      goto LAB_005c6451;
    }
    if (eVar2 != VNONRELOC) {
      return;
    }
    uVar3 = (unaff_ESI->u).s.info;
    if (unaff_EBX == uVar3) goto LAB_005c6451;
    OVar4 = OP_MOVE;
  }
  luaK_codeABC(unaff_EDI,OVar4,unaff_EBX,uVar3,0);
LAB_005c6451:
  (unaff_ESI->u).s.info = unaff_EBX;
  unaff_ESI->k = VNONRELOC;
  return;
}
