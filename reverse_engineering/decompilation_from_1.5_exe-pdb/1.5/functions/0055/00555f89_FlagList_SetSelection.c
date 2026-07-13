/*
 * Entry: 00555f89
 * Name: FlagList::SetSelection
 * Namespace: FlagList
 * Signature: void SetSelection(FlagList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagList::SetSelection(FlagList *this,char *param_1)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  ShellBitmap *pSVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  bool bVar9;
  
  iVar8 = 0;
  if (0 < this->count) {
    pcVar6 = this->s->filename;
    pbVar3 = (byte *)param_1;
    pcVar7 = pcVar6;
LAB_00555fa2:
    do {
      bVar1 = *pbVar3;
      bVar9 = bVar1 < (byte)*pcVar6;
      if (bVar1 == *pcVar6) {
        if (bVar1 != 0) {
          bVar1 = pbVar3[1];
          bVar9 = bVar1 < (byte)pcVar6[1];
          if (bVar1 != pcVar6[1]) goto LAB_00555fc0;
          pcVar6 = pcVar6 + 2;
          pbVar3 = pbVar3 + 2;
          if (bVar1 != 0) goto LAB_00555fa2;
        }
        iVar4 = 0;
      }
      else {
LAB_00555fc0:
        iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
      }
      if (iVar4 == 0) {
        this->currentSelection = iVar8;
        pSVar5 = this->shellBitmap;
        if (pSVar5 != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(pSVar5);
          operator_delete(pSVar5);
        }
        pSVar5 = operator_new(0x20);
        if (pSVar5 == (ShellBitmap *)0x0) {
          pSVar5 = (ShellBitmap *)0x0;
        }
        else {
          pSVar5 = ShellBitmap::ShellBitmap
                             (pSVar5,this->s[this->currentSelection].filename,this->xPos,this->yPos)
          ;
        }
        this->shellBitmap = pSVar5;
        InvalidateRect((HWND)this->h,(RECT *)&this->rect,0);
        pcVar6 = this->s[this->currentSelection].filename;
        pcVar7 = Net::pcFlagName;
        do {
          cVar2 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          *pcVar7 = cVar2;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        return;
      }
      iVar8 = iVar8 + 1;
      pcVar6 = pcVar7 + 0x14;
      pbVar3 = (byte *)param_1;
      pcVar7 = pcVar6;
    } while (iVar8 < this->count);
  }
  return;
}
