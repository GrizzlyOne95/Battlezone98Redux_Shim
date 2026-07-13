/*
 * Entry: 004d4498
 * Name: GameObjectDialog::GameObjectDialog
 * Namespace: GameObjectDialog
 * Signature: GameObjectDialog * GameObjectDialog(GameObjectDialog * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectDialog * __thiscall
GameObjectDialog::GameObjectDialog(GameObjectDialog *this,GameObject *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_1->label;
  dlgObj = param_1;
  if (pcVar3 == (char *)0x0) {
    objLabel[0] = '\0';
  }
  else {
    pcVar4 = objLabel;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  iVar2 = (**(code **)param_1->_padding_)();
  if (*(int *)(iVar2 + 0x20) == 0x57494e47) {
    unitProcess = (UnitProcess *)param_1->aiProcess;
    if (unitProcess != (UnitProcess *)0x0) {
      independence = unitProcess->independence;
      cancelled = true;
      return this;
    }
  }
  else {
    unitProcess = (UnitProcess *)0x0;
  }
  independence = 0;
  cancelled = true;
  return this;
}
