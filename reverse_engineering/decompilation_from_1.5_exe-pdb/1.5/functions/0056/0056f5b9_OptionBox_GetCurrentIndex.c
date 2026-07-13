/*
 * Entry: 0056f5b9
 * Name: OptionBox::GetCurrentIndex
 * Namespace: OptionBox
 * Signature: int GetCurrentIndex(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::GetCurrentIndex(OptionBox *this)

{
  if (this->nItemCount == 0) {
    return -1;
  }
  return this->nOptionMode;
}
