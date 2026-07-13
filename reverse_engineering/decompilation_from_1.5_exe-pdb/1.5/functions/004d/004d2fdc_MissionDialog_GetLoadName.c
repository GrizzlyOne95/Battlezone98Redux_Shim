/*
 * Entry: 004d2fdc
 * Name: MissionDialog::GetLoadName
 * Namespace: MissionDialog
 * Signature: bool GetLoadName(MissionDialog * this, char * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall MissionDialog::GetLoadName(MissionDialog *this,char *param_1,bool param_2)

{
  bool bVar1;
  BOOL BVar2;
  DWORD DVar3;
  
  (this->ofn).lpstrFile = param_1;
  if (param_2) {
    (this->ofn).lpstrTitle = "Load BattleZone Mission";
    (this->ofn).lpstrFilter = "BattleZone Missions (*.BZN)";
    (this->ofn).lpstrInitialDir = "addon";
    (this->ofn).lpstrDefExt = "msn";
  }
  else {
    (this->ofn).lpstrTitle = "Load BattleZone Saved Game";
    (this->ofn).lpstrFilter = "BattleZone Saved Games (*.SAV)";
    (this->ofn).lpstrInitialDir = "save";
    (this->ofn).lpstrDefExt = "sav";
  }
  (this->ofn).Flags = 0x1804;
  UnlockMouse();
  BVar2 = GetOpenFileNameA((LPOPENFILENAMEA)this);
  LockMouse();
  if (BVar2 == 0) {
    DVar3 = CommDlgExtendedError();
    if (DVar3 != 0) {
      DEBUG_systemWarning("Load Dialog Failed (see cderr.h): 0x%4x");
    }
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}
