/*
 * Entry: 00550e37
 * Name: FlagList::GetSelection
 * Namespace: FlagList
 * Signature: char * GetSelection(FlagList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall FlagList::GetSelection(FlagList *this)

{
  int iVar1;
  
  iVar1 = this->currentSelection;
  if ((-1 < iVar1) && (iVar1 < this->count)) {
    return this->s[iVar1].filename;
  }
  return (char *)0x0;
}
