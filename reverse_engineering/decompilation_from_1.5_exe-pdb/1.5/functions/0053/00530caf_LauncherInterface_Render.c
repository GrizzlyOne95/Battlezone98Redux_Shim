/*
 * Entry: 00530caf
 * Name: LauncherInterface::Render
 * Namespace: LauncherInterface
 * Signature: void Render(LauncherInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall LauncherInterface::Render(LauncherInterface *this)

{
  WeaponClass *pWVar1;
  ulong uVar2;
  Weapon *pWVar3;
  GameObject *pGVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  long64 *plVar7;
  tagPOINT tVar8;
  CAMERA *pCVar9;
  float *pfVar10;
  GAS_PREP_INFO local_68;
  float local_4c;
  Carrier *local_48;
  float local_44;
  uint local_40;
  long *local_3c;
  int local_38;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((GameObject::userObject != (GameObject *)0x0) &&
     (local_48 = GameObject::userObject->carrier, local_48 != (Carrier *)0x0)) {
    local_38 = 0;
    local_40 = local_48->selected;
    local_3c = this->state;
    do {
      if ((local_40 & 1 << ((byte)local_38 & 0x1f)) != 0) {
        pWVar3 = Carrier::GetWeapon(local_48,local_38);
        pWVar1 = pWVar3->weaponClass;
        uVar2 = pWVar1->sig;
        if ((((uVar2 == 0x4c4e4348) || (uVar2 == 0x54484d4c)) || (uVar2 == 0x494d474c)) ||
           (uVar2 == 0x5244524c)) {
          if (*local_3c < (int)pWVar3[1].obj) {
            plVar7 = (long64 *)(pWVar1[1].odf + 0xc);
            if (pWVar3[1].obj != (_OBJ76 *)(*(int *)(pWVar1[1].wpnName + 4) + -1)) {
              plVar7 = &pWVar1[1].cfg;
            }
            if ((char)*plVar7 != '\0') {
              InitGASCtrl(&local_34);
              InitGASPrep(&local_68);
              StartGASEvent((char *)plVar7,(_OBJ76 *)0x0,&local_34,&local_68);
            }
          }
          *local_3c = (long)pWVar3[1].obj;
          pGVar4 = GameObject::GetObj(*(int *)&pWVar3[1].field_0x1c);
          pGVar5 = GameObject::GetObj((int)pWVar3[1].M.right_y);
          if (pGVar5 != (GameObject *)0x0) {
            pfVar10 = &local_4c;
            pCVar9 = DisplayInterface::currentCamera;
            pVVar6 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
            tVar8 = WorldToScreen(pVVar6,pCVar9,pfVar10);
            if (0.0 < local_4c) {
              DrawSprite(DisplayInterface::currentBuffer,*(int *)(pWVar1[1].odf + 8),tVar8.x,tVar8.y
                         ,0x250004);
            }
          }
          if ((pGVar4 != (GameObject *)0x0) && (pGVar4 != pGVar5)) {
            pfVar10 = &local_44;
            pCVar9 = DisplayInterface::currentCamera;
            pVVar6 = (VECTOR_3D *)(**(code **)(pGVar4->_padding_ + 0xc))();
            tVar8 = WorldToScreen(pVVar6,pCVar9,pfVar10);
            if (0.0 < local_44) {
              DrawSprite(DisplayInterface::currentBuffer,*(int *)&pWVar1[1].field_0x14,tVar8.x,
                         tVar8.y,0x250004);
            }
          }
        }
      }
      local_38 = local_38 + 1;
      local_3c = local_3c + 1;
    } while (local_38 < 5);
  }
  return;
}
