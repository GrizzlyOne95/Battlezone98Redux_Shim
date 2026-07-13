/*
 * Entry: 00570dd4
 * Name: GetPlanetDesc
 * Namespace: Global
 * Signature: int GetPlanetDesc(int param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPlanetDesc(int param_1,int param_2,char *param_3)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  if (param_1 == 1) {
    iVar3 = USAMissionList[param_2].nPlanet;
LAB_00570dee:
    if (iVar3 == 1) goto LAB_00570e5f;
    if (iVar3 != 2) {
      if (iVar3 == 3) {
        pcVar4 = "venus.txt";
LAB_00570e32:
        *(undefined4 *)param_3 = *(undefined4 *)pcVar4;
        *(undefined4 *)(param_3 + 4) = *(undefined4 *)(pcVar4 + 4);
        *(undefined2 *)(param_3 + 8) = *(undefined2 *)(pcVar4 + 8);
        return 1;
      }
      if (iVar3 == 4) {
        pcVar4 = "io.txt";
      }
      else {
        if (iVar3 != 5) {
          if (iVar3 == 6) {
            pcVar4 = "titan.txt";
            goto LAB_00570e32;
          }
          if (iVar3 != 7) goto LAB_00570e5f;
          pcVar4 = "lles.txt";
          builtin_strncpy(param_3,"achi",4);
          param_3 = param_3 + 4;
          goto LAB_00570e64;
        }
        pcVar4 = "pa.txt";
        builtin_strncpy(param_3,"euro",4);
        param_3 = param_3 + 4;
      }
      *(undefined4 *)param_3 = *(undefined4 *)pcVar4;
      pcVar2 = param_3 + 6;
      pcVar1 = pcVar4 + 6;
      *(undefined2 *)(param_3 + 4) = *(undefined2 *)(pcVar4 + 4);
      goto LAB_00570e66;
    }
    pcVar4 = "mars.txt";
  }
  else {
    if (param_1 == 2) {
      iVar3 = USSRMissionList[param_2].nPlanet;
      goto LAB_00570dee;
    }
LAB_00570e5f:
    pcVar4 = "moon.txt";
  }
LAB_00570e64:
  *(undefined4 *)param_3 = *(undefined4 *)pcVar4;
  pcVar2 = param_3 + 8;
  pcVar1 = pcVar4 + 8;
  *(undefined4 *)(param_3 + 4) = *(undefined4 *)(pcVar4 + 4);
LAB_00570e66:
  *pcVar2 = *pcVar1;
  return 1;
}
