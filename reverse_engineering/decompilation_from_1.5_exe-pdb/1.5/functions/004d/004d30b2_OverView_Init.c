/*
 * Entry: 004d30b2
 * Name: OverView::Init
 * Namespace: OverView
 * Signature: void Init(OverView * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::Init(OverView *this)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = &CURSOR_MAP[0].index;
  do {
    iVar1 = GetSpriteIndex(((<unnamed_type_CURSOR_MAP> *)(piVar2 + -1))->name);
    *piVar2 = iVar1;
    piVar2 = piVar2 + 2;
  } while ((int)piVar2 < 0x62a5dc);
  return;
}
