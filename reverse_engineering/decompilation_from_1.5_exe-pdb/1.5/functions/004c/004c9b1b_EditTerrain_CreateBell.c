/*
 * Entry: 004c9b1b
 * Name: EditTerrain::CreateBell
 * Namespace: EditTerrain
 * Signature: void CreateBell(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::CreateBell(EditTerrain *this)

{
  float (*pafVar1) [64];
  int iVar2;
  float10 fVar3;
  int local_14;
  float (*local_10) [64];
  
  this->bellSD = this->brushSD;
  this->bellWidth = this->brushWidth;
  this->bellDepth = this->brushDepth;
  local_14 = 0;
  if (-1 < this->brushDepth) {
    local_10 = this->bell;
    do {
      iVar2 = 0;
      pafVar1 = local_10;
      if (-1 < this->brushWidth) {
        do {
          fVar3 = (float10)__CIexp();
          (*pafVar1)[0] = (float)fVar3;
          iVar2 = iVar2 + 1;
          pafVar1 = (float (*) [64])(*pafVar1 + 1);
        } while (iVar2 <= this->brushWidth);
      }
      local_14 = local_14 + 1;
      local_10 = local_10 + 1;
    } while (local_14 <= this->brushDepth);
  }
  return;
}
