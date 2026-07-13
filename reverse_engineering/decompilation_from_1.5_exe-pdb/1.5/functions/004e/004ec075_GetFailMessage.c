/*
 * Entry: 004ec075
 * Name: GetFailMessage
 * Namespace: Global
 * Signature: char * GetFailMessage(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetFailMessage(void)

{
  if (od.FailText[od.FailMessageNum] != (char *)0x0) {
    if (od.FailMessageNum < 0) {
      return "Warning - no objective failure text found";
    }
    if (od.FailMessageNum < od.NumFails) {
      return od.FailText[od.FailMessageNum];
    }
  }
  if (od.FailMessageNum < 0) {
    return "Warning - no objective failure text found";
  }
  return (char *)0x0;
}
