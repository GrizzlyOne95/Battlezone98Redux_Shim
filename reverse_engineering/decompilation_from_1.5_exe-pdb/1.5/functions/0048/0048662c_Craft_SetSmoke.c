/*
 * Entry: 0048662c
 * Name: Craft::SetSmoke
 * Namespace: Craft
 * Signature: void SetSmoke(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::SetSmoke(Craft *this,float param_1)

{
  SmokeEmitter *pSVar1;
  ulong *puVar2;
  
  if (0.5 <= param_1) {
    puVar2 = &this->vhcl->flags;
    if ((*puVar2 & 0x100) != 0) {
      *puVar2 = *puVar2 & 0xfffffeff;
      this->smokeTimer = 0.0;
    }
  }
  else {
    pSVar1 = smokeEffect.smokeBlack;
    if (((0.1 <= param_1) && (pSVar1 = smokeEffect.smokeBrown, 0.2 <= param_1)) &&
       (pSVar1 = smokeEffect.smokeTan, 0.3 <= param_1)) {
      pSVar1 = smokeEffect.smokeWhite;
    }
    this->smokeEmitter = pSVar1;
    puVar2 = &this->vhcl->flags;
    if ((*puVar2 & 0x100) == 0) {
      *puVar2 = *puVar2 | 0x100;
    }
  }
  return;
}
