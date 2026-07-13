/*
 * Entry: 004cfed0
 * Name: TimeAdjItem::Display
 * Namespace: TimeAdjItem
 * Signature: void Display(TimeAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall TimeAdjItem::Display(TimeAdjItem *this)

{
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_58,"time scale (%.1f)",(double)(TICKS2SEC * 1000.0));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  return;
}
