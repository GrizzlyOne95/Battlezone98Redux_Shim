/*
 * Entry: 004d2f52
 * Name: MissionDialog::GetSaveName
 * Namespace: MissionDialog
 * Signature: bool GetSaveName(MissionDialog * this, char * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall MissionDialog::GetSaveName(MissionDialog *this,char *param_1,bool param_2)

{
  bool bVar1;
  BOOL BVar2;
  DWORD DVar3;
  
  (this->ofn).lpstrFile = param_1;
  if (param_2) {
    (this->ofn).lpstrTitle = "Save BattleZone Misson";
    (this->ofn).lpstrFilter = "BattleZone Mission (*.BZN)";
    (this->ofn).lpstrInitialDir = "addon";
    (this->ofn).lpstrDefExt = "bzn";
  }
  else {
    (this->ofn).lpstrTitle = "Save BattleZone Game";
    (this->ofn).lpstrFilter = "BattleZone Saved Games (*.SAV)";
    (this->ofn).lpstrInitialDir = "save";
    (this->ofn).lpstrDefExt = "sav";
  }
  (this->ofn).Flags = 6;
  UnlockMouse();
  BVar2 = GetSaveFileNameA((LPOPENFILENAMEA)this);
  LockMouse();
  if (BVar2 == 0) {
    DVar3 = CommDlgExtendedError();
    if (DVar3 != 0) {
      DEBUG_systemWarning("Save Dialog Failed (see cderr.h): 0x%4x");
    }
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}
