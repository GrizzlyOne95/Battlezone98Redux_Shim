/*
 * Entry: 004af2c3
 * Name: Scrap_CleanupRange
 * Namespace: Global
 * Signature: void Scrap_CleanupRange(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scrap_CleanupRange(void)

{
  Range *pRVar1;
  
  pRVar1 = Scrap::scrapRange;
  if (Scrap::scrapRange != (Range *)0x0) {
    Range::~Range(Scrap::scrapRange);
    operator_delete(pRVar1);
  }
  Scrap::scrapRange = (Range *)0x0;
  return;
}
