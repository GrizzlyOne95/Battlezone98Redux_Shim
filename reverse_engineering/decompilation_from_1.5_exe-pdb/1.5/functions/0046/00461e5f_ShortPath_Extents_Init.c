/*
 * Entry: 00461e5f
 * Name: ShortPath::Extents::Init
 * Namespace: ShortPath::Extents
 * Signature: void Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Extents::Init(void)

{
  longlong lVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int extraout_EAX;
  int extraout_EAX_00;
  uint uVar6;
  float10 fVar7;
  
  xDir = 1;
  zDir = 1;
  fVar2 = goal.x;
  fVar3 = start.x;
  if (goal.x < start.x) {
    xDir = -1;
    fVar2 = start.x;
    fVar3 = goal.x;
  }
  fVar4 = goal.z;
  fVar5 = start.z;
  if (goal.z < start.z) {
    zDir = -1;
    fVar4 = start.z;
    fVar5 = goal.z;
  }
  e.z0 = fVar5 - 0.01;
  e.x1 = fVar2 + 0.01;
  e.z1 = fVar4 + 0.01;
  fVar7 = (float10)floor((double)((fVar3 - 0.01) * 0.1));
  e.x0 = (float)(fVar7 * (float10)10.0);
  fVar7 = (float10)floor((double)(e.z0 * 0.1));
  e.z0 = (float)(fVar7 * (float10)10.0);
  ceil((double)((e.x1 - e.x0) * 0.1));
  _ftol2_sse();
  dx = extraout_EAX;
  ceil((double)((e.z1 - e.z0) * 0.1));
  _ftol2_sse();
  uVar6 = extraout_EAX_00 * dx;
  e.x1 = (float)dx * 10.0 + e.x0;
  lVar1 = (ulonglong)uVar6 * 4;
  e.z1 = (float)extraout_EAX_00 * 10.0 + e.z0;
  dz = extraout_EAX_00;
  cellNodes = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  memset(cellNodes,0,uVar6 * 4);
  return;
}
