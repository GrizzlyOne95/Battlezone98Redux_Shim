/*
 * Entry: 005c61d0
 * Name: luaK_nil
 * Namespace: Global
 * Signature: void luaK_nil(FuncState * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_nil(FuncState *param_1,int param_2,int param_3)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_1->pc;
  if (param_1->lasttarget < iVar2) {
    if (iVar2 == 0) {
      if ((int)(uint)param_1->nactvar <= param_2) {
        return;
      }
    }
    else {
      puVar1 = param_1->f->code + iVar2 + -1;
      uVar3 = *puVar1;
      if (((((byte)uVar3 & 0x3f) == 3) && ((int)(uVar3 >> 6 & 0xff) <= param_2)) &&
         (param_2 <= (int)((uVar3 >> 0x17) + 1))) {
        if (param_3 + param_2 + -1 <= (int)(uVar3 >> 0x17)) {
          return;
        }
        *puVar1 = (param_3 + param_2 + -1) * 0x800000 | uVar3 & 0x7fffff;
        return;
      }
    }
  }
  luaK_codeABC(param_1,OP_LOADNIL,param_2,param_2 + -1 + param_3,0);
  return;
}
