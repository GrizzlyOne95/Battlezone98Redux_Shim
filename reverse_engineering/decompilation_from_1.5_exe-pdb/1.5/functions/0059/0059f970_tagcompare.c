/*
 * Entry: 0059f970
 * Name: tagcompare
 * Namespace: Global
 * Signature: int tagcompare(char * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl tagcompare(char *param_1,char *param_2,int param_3)

{
  char *in_EAX;
  int iVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  if (0 < (int)param_1) {
    iVar3 = in_ECX - (int)in_EAX;
    do {
      iVar1 = toupper((int)in_EAX[iVar3]);
      iVar2 = toupper((int)*in_EAX);
      if (iVar1 != iVar2) {
        return 1;
      }
      iVar4 = iVar4 + 1;
      in_EAX = in_EAX + 1;
    } while (iVar4 < (int)param_1);
  }
  return 0;
}
