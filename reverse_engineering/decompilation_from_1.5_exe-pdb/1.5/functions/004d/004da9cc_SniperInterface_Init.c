/*
 * Entry: 004da9cc
 * Name: SniperInterface::Init
 * Namespace: SniperInterface
 * Signature: void Init(SniperInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperInterface::Init(SniperInterface *this)

{
  int iVar1;
  CAMERA *pCVar2;
  float *pfVar3;
  CAMERA local_3b4;
  float local_1dc [118];
  
  iVar1 = GetSpriteIndex("sight");
  this->crosshair = iVar1;
  iVar1 = GetSpriteIndex("particle.0");
  this->eyepoint = iVar1;
  pCVar2 = Camera_Init(&local_3b4,&Device.Viewport,1.1257373,1.0,500.0,10.0);
  pfVar3 = local_1dc;
  for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = pCVar2->Orig_x;
    pCVar2 = (CAMERA *)&pCVar2->Orig_y;
    pfVar3 = pfVar3 + 1;
  }
  pfVar3 = local_1dc;
  pCVar2 = &this->camera;
  for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
    pCVar2->Orig_x = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pCVar2 = (CAMERA *)&pCVar2->Orig_y;
  }
  this->enabled = false;
  return;
}
