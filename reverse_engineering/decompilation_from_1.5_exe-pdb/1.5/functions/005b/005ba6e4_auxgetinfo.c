/*
 * Entry: 005ba6e4
 * Name: auxgetinfo
 * Namespace: Global
 * Signature: int auxgetinfo(lua_State * param_1, char * param_2, lua_Debug * param_3, Closure * param_4, CallInfo * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
auxgetinfo(lua_State *param_1,char *param_2,lua_Debug *param_3,Closure *param_4,CallInfo *param_5)

{
  char cVar1;
  int in_EAX;
  char *pcVar2;
  int iVar3;
  char *in_ECX;
  Closure *unaff_EBX;
  lua_State *unaff_ESI;
  int unaff_EDI;
  int local_8;
  
  local_8 = 1;
  if (param_2 == (char *)0x0) {
    info_tailcall((lua_Debug *)unaff_ESI);
    local_8 = 1;
  }
  else {
    for (; cVar1 = *in_ECX, cVar1 != '\0'; in_ECX = in_ECX + 1) {
      if (cVar1 != 'L') {
        if (cVar1 == 'S') {
          funcinfo((lua_Debug *)unaff_ESI,unaff_EBX);
        }
        else if (cVar1 != 'f') {
          if (cVar1 == 'l') {
            if (in_EAX == 0) {
              iVar3 = -1;
            }
            else {
              iVar3 = currentline(unaff_ESI,(CallInfo *)&unaff_EBX->c);
            }
            *(int *)(unaff_EDI + 0x14) = iVar3;
          }
          else if (cVar1 == 'n') {
            if (in_EAX == 0) {
              pcVar2 = (char *)0x0;
            }
            else {
              pcVar2 = getfuncname(param_1,(CallInfo *)(unaff_EDI + 4),(char **)unaff_ESI);
            }
            *(char **)(unaff_EDI + 8) = pcVar2;
            if (pcVar2 == (char *)0x0) {
              *(undefined4 *)(unaff_EDI + 4) = 0;
              *(char **)(unaff_EDI + 8) = "";
            }
          }
          else if (cVar1 == 'u') {
            *(uint *)(unaff_EDI + 0x18) = (uint)(byte)param_2[7];
          }
          else {
            local_8 = 0;
          }
        }
      }
    }
  }
  return local_8;
}
