/*
 * Entry: 004621bf
 * Name: ShortPath::Init
 * Namespace: ShortPath
 * Signature: void Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Init(void)

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
  
  Extents::xDir = 1;
  Extents::zDir = 1;
  fVar2 = goal.x;
  fVar3 = start.x;
  if (goal.x < start.x) {
    Extents::xDir = -1;
    fVar2 = start.x;
    fVar3 = goal.x;
  }
  fVar4 = goal.z;
  fVar5 = start.z;
  if (goal.z < start.z) {
    Extents::zDir = -1;
    fVar4 = start.z;
    fVar5 = goal.z;
  }
  Extents::e.z0 = fVar5 - 0.01;
  Extents::e.x1 = fVar2 + 0.01;
  Extents::e.z1 = fVar4 + 0.01;
  fVar7 = (float10)floor((double)((fVar3 - 0.01) * 0.1));
  Extents::e.x0 = (float)(fVar7 * (float10)10.0);
  fVar7 = (float10)floor((double)(Extents::e.z0 * 0.1));
  Extents::e.z0 = (float)(fVar7 * (float10)10.0);
  ceil((double)((Extents::e.x1 - Extents::e.x0) * 0.1));
  _ftol2_sse();
  Extents::dx = extraout_EAX;
  ceil((double)((Extents::e.z1 - Extents::e.z0) * 0.1));
  _ftol2_sse();
  uVar6 = extraout_EAX_00 * Extents::dx;
  Extents::e.x1 = (float)Extents::dx * 10.0 + Extents::e.x0;
  lVar1 = (ulonglong)uVar6 * 4;
  Extents::e.z1 = (float)extraout_EAX_00 * 10.0 + Extents::e.z0;
  Extents::dz = extraout_EAX_00;
  Extents::cellNodes = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  memset(Extents::cellNodes,0,uVar6 * 4);
  return;
}
