/*
 * Entry: 004db76b
 * Name: TargetCam::Init
 * Namespace: TargetCam
 * Signature: void Init(TargetCam * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TargetCam::Init(TargetCam *this)

{
  CAMERA *pCVar1;
  int iVar2;
  float *pfVar3;
  CAMERA local_3b4;
  float local_1dc [118];
  
  pCVar1 = Camera_Init(&local_3b4,&Device.Viewport,0.87266463,1.0,250.0,1.0);
  pfVar3 = local_1dc;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = pCVar1->Orig_x;
    pCVar1 = (CAMERA *)&pCVar1->Orig_y;
    pfVar3 = pfVar3 + 1;
  }
  pfVar3 = local_1dc;
  pCVar1 = &this->camera;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    pCVar1->Orig_x = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pCVar1 = (CAMERA *)&pCVar1->Orig_y;
  }
  this->targetObj = (GameObject *)0x0;
  this->targetEye = (_OBJ76 *)0x0;
  this->enabled = false;
  return;
}
