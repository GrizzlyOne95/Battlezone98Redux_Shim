/*
 * Entry: 0040adb7
 * Name: AddRect
 * Namespace: Global
 * Signature: void AddRect(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddRect(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  tagRECT *ptVar2;
  
  iVar1 = rectCount;
  ptVar2 = rects + rectCount;
  rectCount = rectCount + 1;
  ptVar2->left = param_1;
  rects[iVar1].top = param_2;
  rects[iVar1].right = param_3;
  rects[iVar1].bottom = param_4;
  return;
}
