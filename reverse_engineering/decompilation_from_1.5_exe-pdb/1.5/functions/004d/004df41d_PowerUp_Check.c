/*
 * Entry: 004df41d
 * Name: PowerUp_Check
 * Namespace: Global
 * Signature: void PowerUp_Check(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PowerUp_Check(void)

{
  DWORD DVar1;
  
  DVar1 = Get_TimeNow();
  if (dwPowerUpCheck < DVar1) {
    dwPowerUpCheck = DVar1 + 60000;
    LoadPlayerData();
    return;
  }
  return;
}
