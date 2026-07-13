/*
 * Entry: 0056f607
 * Name: OptionBox::CleanItemList
 * Namespace: OptionBox
 * Signature: int CleanItemList(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::CleanItemList(OptionBox *this)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0x32;
  piVar1 = &this->itemList[0].nReturnNum;
  do {
    builtin_strncpy(((_OptionItem *)(piVar1 + -0x40))->cOptionName,"NULL",4);
    *(char *)(piVar1 + -0x3f) = '\0';
    *piVar1 = 0;
    piVar1 = piVar1 + 0x41;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  this->nItemCount = 0;
  return 1;
}
