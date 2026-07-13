/*
 * Entry: 0056f59e
 * Name: OptionBox::GetCurrentValue
 * Namespace: OptionBox
 * Signature: int GetCurrentValue(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::GetCurrentValue(OptionBox *this)

{
  if (this->nItemCount == 0) {
    return -1;
  }
  return this->itemList[this->nOptionMode].nReturnNum;
}
