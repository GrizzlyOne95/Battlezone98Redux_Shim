/*
 * Entry: 0040af31
 * Name: AOI::Init
 * Namespace: AOI
 * Signature: void Init(long param_1, long param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AOI::Init(long param_1,long param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int **ppiVar2;
  
  gridLeft = param_1;
  gridTop = param_2;
  gridScale = param_3;
  gridRows = param_4;
  gridColumns = param_5;
  iVar1 = 0x20;
  ppiVar2 = values[0];
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppiVar2 = (int *)0x0;
    ppiVar2 = ppiVar2 + 1;
  }
  hasArea[0] = false;
  hasArea[1] = false;
  hasArea[2] = false;
  hasArea[3] = false;
  hasArea[4] = false;
  hasArea[5] = false;
  hasArea[6] = false;
  hasArea[7] = false;
  hasArea[8] = false;
  hasArea[9] = false;
  hasArea[10] = false;
  hasArea[0xb] = false;
  hasArea[0xc] = false;
  hasArea[0xd] = false;
  hasArea[0xe] = false;
  hasArea[0xf] = false;
  ppiVar2 = forces;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppiVar2 = (int *)0x0;
    ppiVar2 = ppiVar2 + 1;
  }
  recalc = true;
  return;
}
