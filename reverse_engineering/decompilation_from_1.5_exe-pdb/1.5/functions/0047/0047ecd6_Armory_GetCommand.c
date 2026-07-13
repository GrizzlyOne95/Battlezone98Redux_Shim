/*
 * Entry: 0047ecd6
 * Name: Armory::GetCommand
 * Namespace: Armory
 * Signature: AiCommand GetCommand(Armory * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall Armory::GetCommand(Armory *this,VECTOR_3D *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetActiveMode((GameObject *)this);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      return CMD_GO;
    }
    if (0x18 < iVar1) {
      iVar1 = *(int *)(iVar1 + 0x20);
      if (iVar1 == 0x414d4d4f) {
        return CMD_GET_RELOAD;
      }
      if (iVar1 == 0x43504f44) {
        return CMD_GET_CAMERA;
      }
      if (iVar1 == 0x524b4954) {
        return CMD_GET_REPAIR;
      }
      if (iVar1 == 0x5745504e) {
        return CMD_GET_WEAPON;
      }
      if (iVar1 == 0x5752434b) {
        return CMD_GET_BOMB;
      }
    }
  }
  return CMD_NONE;
}
