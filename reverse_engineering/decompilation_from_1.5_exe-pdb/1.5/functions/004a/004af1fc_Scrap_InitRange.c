/*
 * Entry: 004af1fc
 * Name: Scrap_InitRange
 * Namespace: Global
 * Signature: void Scrap_InitRange(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scrap_InitRange(void)

{
  Range *this;
  
  this = operator_new(0x40);
  if (this == (Range *)0x0) {
    Scrap::scrapRange = (Range *)0x0;
  }
  else {
    Scrap::scrapRange =
         Range::Range(this,100.0,100.0,(double)grid_rect.top,(double)grid_rect.bottom,
                      (double)grid_rect.left,(double)grid_rect.right,0x300);
  }
  updateScrap = true;
  return;
}
