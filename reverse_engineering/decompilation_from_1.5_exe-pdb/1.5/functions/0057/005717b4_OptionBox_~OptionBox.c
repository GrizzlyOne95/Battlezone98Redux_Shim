/*
 * Entry: 005717b4
 * Name: OptionBox::~OptionBox
 * Namespace: OptionBox
 * Signature: void ~OptionBox(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OptionBox::~OptionBox(OptionBox *this)

{
  TextLabel *this_00;
  
  this_00 = this->dataBox;
  if (this_00 != (TextLabel *)0x0) {
    TextLabel::~TextLabel(this_00);
    operator_delete(this_00);
    this->dataBox = (TextLabel *)0x0;
  }
  return;
}
