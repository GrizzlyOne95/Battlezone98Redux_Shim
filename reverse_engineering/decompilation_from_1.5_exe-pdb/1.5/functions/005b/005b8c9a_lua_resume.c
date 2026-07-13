/*
 * Entry: 005b8c9a
 * Name: lua_resume
 * Namespace: Global
 * Signature: int lua_resume(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_resume(lua_State *param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  char *unaff_ESI;
  char *pcVar4;
  
  if ((param_1->status == '\x01') ||
     ((param_1->status == '\0' && (param_1->ci == param_1->base_ci)))) {
    if (param_1->nCcalls < 200) {
      uVar1 = param_1->nCcalls + 1;
      param_1->nCcalls = uVar1;
      param_1->baseCcalls = uVar1;
      uVar3 = luaD_rawrunprotected(param_1,resume,param_1->top + -param_2);
      if (uVar3 == 0) {
        uVar3 = (uint)param_1->status;
      }
      else {
        param_1->status = (uchar)uVar3;
        luaD_seterrorobj(param_1,uVar3,param_1->top);
        param_1->ci->top = param_1->top;
      }
      param_1->nCcalls = param_1->nCcalls - 1;
      return uVar3;
    }
    pcVar4 = "C stack overflow";
  }
  else {
    pcVar4 = "cannot resume non-suspended coroutine";
  }
  iVar2 = resume_error((lua_State *)pcVar4,unaff_ESI);
  return iVar2;
}
