/*
 * Entry: 005b3290
 * Name: render_line0
 * Namespace: Global
 * Signature: void render_line0(int param_1, int param_2, int param_3, int param_4, int param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl render_line0(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = param_3;
  uVar6 = in_EAX - param_3;
  iVar3 = in_ECX - param_2;
  iVar2 = (int)uVar6 / iVar3;
  iVar4 = iVar2 + -1;
  if (-1 < (int)uVar6) {
    iVar4 = iVar2 + 1;
  }
  uVar5 = iVar2 * iVar3 >> 0x1f;
  param_3 = 0;
  if (in_ECX < param_1) {
    param_1 = in_ECX;
  }
  if (param_2 < param_1) {
    *(int *)(param_4 + param_2 * 4) = iVar7;
  }
  while (param_2 = param_2 + 1, param_2 < param_1) {
    param_3 = param_3 + (((uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f)) -
                        ((iVar2 * iVar3 ^ uVar5) - uVar5));
    iVar1 = iVar2;
    if (iVar3 <= param_3) {
      param_3 = param_3 - iVar3;
      iVar1 = iVar4;
    }
    iVar7 = iVar7 + iVar1;
    *(int *)(param_4 + param_2 * 4) = iVar7;
  }
  return;
}
