/*
 * Entry: 005b3b10
 * Name: post_Y
 * Namespace: Global
 * Signature: int post_Y(int * param_1, int * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl post_Y(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int in_ECX;
  int in_EDX;
  
  iVar2 = *(int *)(in_EAX + in_ECX * 4);
  if (iVar2 < 0) {
    return *(int *)(in_EDX + in_ECX * 4);
  }
  iVar1 = *(int *)(in_EDX + in_ECX * 4);
  if (-1 < iVar1) {
    iVar2 = iVar2 + iVar1 >> 1;
  }
  return iVar2;
}
