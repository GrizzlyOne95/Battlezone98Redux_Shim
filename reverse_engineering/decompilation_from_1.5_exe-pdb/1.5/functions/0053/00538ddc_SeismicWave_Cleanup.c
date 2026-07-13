/*
 * Entry: 00538ddc
 * Name: SeismicWave::Cleanup
 * Namespace: SeismicWave
 * Signature: void Cleanup(SeismicWave * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SeismicWave::Cleanup(SeismicWave *this)

{
  short sVar1;
  ushort *puVar2;
  int iVar3;
  short *psVar4;
  long lVar5;
  int local_8;
  
  local_8 = (this->zMin).i;
  psVar4 = this->deltaH;
  if (local_8 <= (this->zMax).i) {
    iVar3 = (this->xMax).i;
    do {
      for (lVar5 = (this->xMin).i; lVar5 <= iVar3; lVar5 = lVar5 + 1) {
        puVar2 = GetZonePtr(lVar5,local_8);
        sVar1 = *psVar4;
        psVar4 = psVar4 + 1;
        *puVar2 = (*puVar2 & 0xf000) + ((*puVar2 & 0xfff) - sVar1);
        iVar3 = (this->xMax).i;
      }
      local_8 = local_8 + 1;
    } while (local_8 <= (this->zMax).i);
  }
  RemoveCoplanarFlags((this->xMin).i,(this->zMin).i,(this->xMax).i,(this->zMax).i);
  Ordnance::Cleanup((Ordnance *)this);
  return;
}
