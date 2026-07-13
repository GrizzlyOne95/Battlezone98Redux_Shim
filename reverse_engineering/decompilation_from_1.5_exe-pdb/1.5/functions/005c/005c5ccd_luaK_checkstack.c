/*
 * Entry: 005c5ccd
 * Name: luaK_checkstack
 * Namespace: Global
 * Signature: void luaK_checkstack(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_checkstack(FuncState *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1->freereg + param_2;
  if ((int)(uint)param_1->f->maxstacksize < iVar1) {
    if (0xf9 < iVar1) {
      luaX_syntaxerror(param_1->ls,"function or expression too complex");
    }
    param_1->f->maxstacksize = (uchar)iVar1;
  }
  return;
}
