/*
 * Entry: 0047ed2d
 * Name: Armory::GetCommand
 * Namespace: Armory
 * Signature: AiCommand GetCommand(Armory * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall Armory::GetCommand(Armory *this,GameObject *param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  Carrier *pCVar5;
  
  if (param_1 == (GameObject *)0x0) {
    return CMD_NONE;
  }
  iVar3 = GameObject::GetActiveMode((GameObject *)this);
  if (iVar3 == 0) {
    return CMD_NONE;
  }
  if (iVar3 == 9) {
    return CMD_NONE;
  }
  if (iVar3 == 1) {
    if ((Armory *)param_1 == this) {
      return CMD_NONE;
    }
    piVar1 = &param_1->_padding_;
    iVar3 = (**(code **)*piVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x53435250) {
      return CMD_NONE;
    }
    iVar3 = (**(code **)*piVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x4745495a) {
      if (*(char *)((int)&param_1[1]._padding_ + 1) != '\0') {
        return CMD_NONE;
      }
      return CMD_GO;
    }
    iVar3 = (**(code **)*piVar1)();
    if (*(int *)(iVar3 + 0x28) == 3) {
      return CMD_GO;
    }
    iVar3 = (**(code **)(*piVar1 + 4))();
    if ((iVar3 == 0) && (param_1->isObjective == false)) {
      return CMD_NONE;
    }
    bVar2 = GameObject::EnemyP((GameObject *)this,param_1);
    if (bVar2) {
      return CMD_NONE;
    }
    iVar3 = (**(code **)*piVar1)();
    if ((*(int *)(iVar3 + 0x28) != 1) &&
       (iVar3 = (**(code **)*piVar1)(), *(int *)(iVar3 + 0x28) != 6)) {
      iVar3 = (**(code **)*piVar1)();
      return -(uint)(*(int *)(iVar3 + 0x28) != 5) & CMD_GO;
    }
    return CMD_FOLLOW;
  }
  if (iVar3 < 0x19) {
    return CMD_NONE;
  }
  piVar1 = &param_1->_padding_;
  iVar4 = (**(code **)*piVar1)();
  if (((*(int *)(iVar4 + 0x28) == 1) ||
      (iVar4 = (**(code **)*piVar1)(), *(int *)(iVar4 + 0x28) == 6)) ||
     (iVar4 = (**(code **)*piVar1)(), *(int *)(iVar4 + 0x28) == 2)) {
    iVar4 = *(int *)(iVar3 + 0x20);
    if (iVar4 == 0x414d4d4f) {
      if ((int)(param_1->maxAmmo ^ 0x33333333U) <= (int)(param_1->curAmmo ^ 0x33333333U)) {
        return CMD_NONE;
      }
      if (param_1->carrier == (Carrier *)0x0) {
        return CMD_NONE;
      }
      return CMD_GET_RELOAD;
    }
    if (iVar4 == 0x43504f44) {
      iVar3 = (**(code **)*piVar1)();
      return -(uint)(*(int *)(iVar3 + 0x28) != 2) & CMD_GET_CAMERA;
    }
    if (iVar4 == 0x524b4954) {
      bVar2 = param_1->curHealth < param_1->maxHealth;
      goto LAB_0047ee8e;
    }
    if (iVar4 == 0x5745504e) {
      pCVar5 = param_1->carrier;
      if (pCVar5 == (Carrier *)0x0) {
        return CMD_NONE;
      }
      iVar4 = 0;
      while( true ) {
        pCVar5 = (Carrier *)pCVar5->hardpoint;
        if ((*(_OBJ76 **)pCVar5 != (_OBJ76 *)0x0) &&
           ((*(_OBJ76 **)pCVar5)->class_id == *(OBJECT_CLASS_T *)(*(int *)(iVar3 + 0x170) + 0x74)))
        break;
        iVar4 = iVar4 + 1;
        if (4 < iVar4) {
          return CMD_NONE;
        }
      }
      return CMD_GET_WEAPON;
    }
    if (iVar4 != 0x5752434b) {
      return CMD_NONE;
    }
    iVar3 = (**(code **)*piVar1)();
    if (*(int *)(iVar3 + 0x20) != 0x4745495a) {
      return CMD_GET_BOMB;
    }
    bVar2 = *(char *)((int)&param_1[1]._padding_ + 1) == '\0';
  }
  else {
    iVar3 = *(int *)(iVar3 + 0x20);
    if (iVar3 == 0x414d4d4f) {
      iVar3 = (**(code **)*piVar1)();
      if (*(int *)(iVar3 + 0x20) != 0x43504f44) {
        return CMD_NONE;
      }
      return CMD_GET_RELOAD;
    }
    if (iVar3 == 0x524b4954) {
      iVar3 = (**(code **)*piVar1)();
      bVar2 = *(int *)(iVar3 + 0x20) == 0x43504f44;
LAB_0047ee8e:
      if (!bVar2) {
        return CMD_NONE;
      }
      return CMD_GET_REPAIR;
    }
    if (iVar3 == 0x5745504e) {
      iVar3 = (**(code **)*piVar1)();
      if (*(int *)(iVar3 + 0x20) != 0x43504f44) {
        return CMD_NONE;
      }
      return CMD_GET_WEAPON;
    }
    bVar2 = iVar3 == 0x5752434b;
  }
  if (!bVar2) {
    return CMD_NONE;
  }
  return CMD_GET_BOMB;
}
