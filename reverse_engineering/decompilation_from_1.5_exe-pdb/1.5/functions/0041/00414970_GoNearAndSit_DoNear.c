/*
 * Entry: 00414970
 * Name: GoNearAndSit::DoNear
 * Namespace: GoNearAndSit
 * Signature: bool DoNear(GoNearAndSit * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoNearAndSit::DoNear(GoNearAndSit *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = *(int *)&this->field_0x14;
  iVar2 = *(int *)(iVar1 + 0x228);
  fVar4 = 0.0;
  if (0.01 <= *(float *)(iVar1 + 0x110)) {
    iVar3 = *(int *)(iVar1 + 0xe8);
    fVar4 = Clamp((*(float *)(iVar3 + 0x40) * *(float *)(iVar1 + 0x128) +
                   *(float *)(iVar1 + 0x124) * *(float *)(iVar3 + 0x3c) +
                  *(float *)(iVar1 + 0x120) * *(float *)(iVar3 + 0x38)) * -0.2,-1.0,1.0);
    *(float *)(iVar2 + 0xd0) = fVar4;
    fVar4 = Clamp((*(float *)(iVar3 + 0x28) * *(float *)(iVar1 + 0x128) +
                   *(float *)(iVar1 + 0x124) * *(float *)(iVar3 + 0x24) +
                  *(float *)(iVar1 + 0x120) * *(float *)(iVar3 + 0x20)) * -0.2,-1.0,1.0);
  }
  else {
    *(undefined4 *)(iVar2 + 0xd0) = 0;
  }
  *(undefined4 *)(iVar2 + 0xd4) = 0;
  *(float *)(iVar2 + 0xcc) = fVar4;
  *(undefined4 *)(iVar2 + 200) = 0;
  *(undefined4 *)(iVar2 + 0xc4) = 0x3f000000;
  return false;
}
