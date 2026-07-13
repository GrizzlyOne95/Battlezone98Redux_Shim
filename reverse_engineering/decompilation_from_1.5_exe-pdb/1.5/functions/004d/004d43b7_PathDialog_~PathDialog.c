/*
 * Entry: 004d43b7
 * Name: PathDialog::~PathDialog
 * Namespace: PathDialog
 * Signature: void ~PathDialog(PathDialog * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDialog::~PathDialog(PathDialog *this)

{
  bool bVar1;
  bool bVar2;
  AOI *pAVar3;
  
  if (cancelled) {
    return;
  }
  if (!defendArea) {
    areaForce = areaForce + 100;
  }
  AiPath::SetLabel(aiPath,pathName);
  pAVar3 = area;
  if (area == (AOI *)0x0) {
    if (isArea == false) goto LAB_004d446e;
    pAVar3 = operator_new(0x18);
    if (pAVar3 != (AOI *)0x0) {
      AOI::AOI(pAVar3,aiPath,2,isInteresting,isInside,areaValue,areaForce);
    }
  }
  else if (isArea == false) {
    AOI::~AOI(area);
    operator_delete(pAVar3);
    area = (AOI *)0x0;
  }
  pAVar3 = area;
  bVar2 = isInteresting;
  bVar1 = isInside;
  if (area != (AOI *)0x0) {
    area->interesting = isInteresting;
    pAVar3->inside = bVar1;
    if (bVar2 == false) {
      areaValue = -1;
      areaForce = 0;
    }
    pAVar3->value = areaValue;
    pAVar3->force = areaForce;
  }
LAB_004d446e:
  AOI::Recalc();
  return;
}
