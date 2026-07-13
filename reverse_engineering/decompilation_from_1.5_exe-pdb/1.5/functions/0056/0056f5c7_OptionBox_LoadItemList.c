/*
 * Entry: 0056f5c7
 * Name: OptionBox::LoadItemList
 * Namespace: OptionBox
 * Signature: int LoadItemList(OptionBox * this, int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::LoadItemList(OptionBox *this,int param_1,char *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  
  if ((this->nItemCount < param_1) || (0x32 < param_1)) {
    iVar2 = -1;
  }
  else {
    iVar2 = (param_1 * 0x104 + 0x24) - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[(int)this + iVar2] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
    this->itemList[param_1].nReturnNum = param_3;
    iVar2 = 1;
  }
  return iVar2;
}
