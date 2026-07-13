/*
 * Entry: 0056f505
 * Name: ShellButton::DrawLabelText
 * Namespace: ShellButton
 * Signature: int DrawLabelText(ShellButton * this, HDC__ * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::DrawLabelText(ShellButton *this,HDC__ *param_1,char *param_2)

{
  int iVar1;
  HGDIOBJ h;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  bool bVar5;
  char *lpchText;
  
  lpchText = this->labelText;
  iVar2 = 5;
  iVar1 = 0;
  bVar5 = true;
  pcVar3 = lpchText;
  pcVar4 = "NULL";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  if (!bVar5) {
    h = SelectObject((HDC)param_1,this->hLabelFont);
    SetBkMode((HDC)param_1,1);
    SetTextColor((HDC)param_1,this->textColor);
    if (param_2 != (char *)0x0) {
      lpchText = param_2;
    }
    DrawTextExA((HDC)param_1,lpchText,-1,(LPRECT)&this->labelRect,0x125,(LPDRAWTEXTPARAMS)0x0);
    if (h != (HGDIOBJ)0x0) {
      SelectObject((HDC)param_1,h);
    }
    hButtonFont = (HFONT__ *)0x0;
    iVar1 = 1;
  }
  return iVar1;
}
