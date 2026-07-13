/*
 * Entry: 005b3090
 * Name: render_point
 * Namespace: Global
 * Signature: int render_point(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl render_point(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint in_EAX;
  uint uVar1;
  int iVar2;
  int in_ECX;
  uint in_EDX;
  uint uVar3;
  
  uVar3 = in_EDX & 0x7fff;
  uVar1 = (in_EAX & 0x7fff) - uVar3;
  iVar2 = (int)(((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) * (in_ECX - param_1)) /
          (param_2 - param_1);
  if ((int)uVar1 < 0) {
    return uVar3 - iVar2;
  }
  return iVar2 + uVar3;
}
