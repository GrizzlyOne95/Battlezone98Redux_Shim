/*
 * Entry: 004191e0
 * Name: PackNumber
 * Namespace: Global
 * Signature: bool PackNumber(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackNumber(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  int extraout_EAX;
  int *unaff_ESI;
  uint unaff_EDI;
  float10 extraout_ST0;
  double dVar3;
  
  dVar3 = lua_tonumber((lua_State *)param_1,(int)param_2);
  if (dVar3 != 0.0) {
    _ftol2_sse();
    if ((float10)extraout_EAX == extraout_ST0) {
      if (extraout_EAX + 0x80U < 0x100) {
        if (unaff_EDI <= *unaff_ESI + 1U) {
          return false;
        }
        pcVar1 = (char *)(*unaff_ESI + -1);
        *pcVar1 = *pcVar1 + '\x01';
        *(char *)*unaff_ESI = (char)extraout_EAX;
        *unaff_ESI = *unaff_ESI + 1;
      }
      else {
        iVar2 = *unaff_ESI;
        if (extraout_EAX + 0x8000U < 0x10000) {
          if (unaff_EDI <= iVar2 + 2U) {
            return false;
          }
          *(char *)(iVar2 + -1) = *(char *)(iVar2 + -1) + '\x02';
          *(short *)*unaff_ESI = (short)extraout_EAX;
          *unaff_ESI = *unaff_ESI + 2;
        }
        else {
          if (unaff_EDI <= iVar2 + 4U) {
            return false;
          }
          *(char *)(iVar2 + -1) = *(char *)(iVar2 + -1) + '\x04';
          *(int *)*unaff_ESI = extraout_EAX;
          *unaff_ESI = *unaff_ESI + 4;
        }
      }
    }
    else {
      if (unaff_EDI <= *unaff_ESI + 8U) {
        return false;
      }
      pcVar1 = (char *)(*unaff_ESI + -1);
      *pcVar1 = *pcVar1 + '\b';
      *(double *)*unaff_ESI = (double)extraout_ST0;
      *unaff_ESI = *unaff_ESI + 8;
    }
  }
  return true;
}
