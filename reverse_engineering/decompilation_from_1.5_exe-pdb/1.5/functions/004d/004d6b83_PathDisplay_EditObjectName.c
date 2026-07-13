/*
 * Entry: 004d6b83
 * Name: PathDisplay::EditObjectName
 * Namespace: PathDisplay
 * Signature: void EditObjectName(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::EditObjectName(PathDisplay *this)

{
  GameObject *pGVar1;
  undefined4 uStack_8;
  
  uStack_8 = this;
  UnlockMouse();
  pGVar1 = GameObjectHandle::GetObj(this->taskWhoHandle);
  GameObjectDialog::GameObjectDialog((GameObjectDialog *)((int)&uStack_8 + 3),pGVar1);
  GameObjectDialog::Execute((GameObjectDialog *)((int)&uStack_8 + 3));
  LockMouse();
  GameObjectDialog::~GameObjectDialog((GameObjectDialog *)((int)&uStack_8 + 3));
  return;
}
