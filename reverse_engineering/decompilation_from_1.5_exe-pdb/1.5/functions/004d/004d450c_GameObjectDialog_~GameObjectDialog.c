/*
 * Entry: 004d450c
 * Name: GameObjectDialog::~GameObjectDialog
 * Namespace: GameObjectDialog
 * Signature: void ~GameObjectDialog(GameObjectDialog * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObjectDialog::~GameObjectDialog(GameObjectDialog *this)

{
  if ((!cancelled) && (objLabel[0] != '\0')) {
    GameObject::SetLabel(dlgObj,objLabel);
    if (unitProcess != (UnitProcess *)0x0) {
      unitProcess->independence = independence;
    }
  }
  return;
}
