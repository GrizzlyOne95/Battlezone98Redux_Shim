/*
 * Entry: 0045dd5a
 * Name: DefaultAllies
 * Namespace: Global
 * Signature: void DefaultAllies(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DefaultAllies(void)

{
  Team *this;
  int iVar1;
  int iVar2;
  
  iVar2 = 1;
  do {
    this = Team::GetTeam(iVar2);
    iVar1 = 1;
    do {
      if (iVar2 == iVar1) {
        Team::Ally(this,iVar1);
      }
      else {
        Team::UnAlly(this,iVar1);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}
