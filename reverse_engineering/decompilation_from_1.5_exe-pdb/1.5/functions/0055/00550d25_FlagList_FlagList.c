/*
 * Entry: 00550d25
 * Name: FlagList::FlagList
 * Namespace: FlagList
 * Signature: FlagList * FlagList(FlagList * this, HWND__ * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlagList * __thiscall FlagList::FlagList(FlagList *this,HWND__ *param_1,int param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  _s *p_Var3;
  _s *p_Var4;
  ShellBitmap *pSVar5;
  char *pcVar6;
  
  this->h = param_1;
  (this->rect).left = param_2;
  this->xPos = param_2;
  this->count = 0;
  this->s = (_s *)0x0;
  param_1 = (HWND__ *)0x0;
  (this->rect).right = param_2 + 0x40;
  (this->rect).top = param_3;
  (this->rect).bottom = param_3 + 0x20;
  this->yPos = param_3;
  pcVar2 = zixMatchWild("flag????.bmp",(int *)&param_1);
  if (pcVar2 != (char *)0x0) {
    p_Var3 = malloc(0x14);
    this->s = p_Var3;
    if (p_Var3 != (_s *)0x0) {
      pcVar6 = p_Var3[this->count].filename;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        *pcVar6 = cVar1;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      while( true ) {
        this->count = this->count + 1;
        param_2 = (int)zixMatchWild("flag????.bmp",(int *)&param_1);
        if ((char *)param_2 == (char *)0x0) break;
        p_Var3 = this->s;
        p_Var4 = realloc(p_Var3,(this->count + 1) * 0x14);
        this->s = p_Var4;
        if (p_Var4 == (_s *)0x0) {
          this->s = p_Var3;
          break;
        }
        pcVar6 = p_Var4[this->count].filename;
        pcVar2 = (char *)param_2;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
          *pcVar6 = cVar1;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
      }
    }
  }
  if (this->count == 0) {
    Net::pcFlagName[0] = '\0';
    this->shellBitmap = (ShellBitmap *)0x0;
  }
  else {
    pcVar2 = this->s->filename;
    pcVar6 = Net::pcFlagName;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      *pcVar6 = cVar1;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    pSVar5 = operator_new(0x20);
    if (pSVar5 == (ShellBitmap *)0x0) {
      pSVar5 = (ShellBitmap *)0x0;
    }
    else {
      pSVar5 = ShellBitmap::ShellBitmap(pSVar5,this->s->filename,this->xPos,this->yPos);
    }
    this->shellBitmap = pSVar5;
  }
  this->currentSelection = 0;
  return this;
}
