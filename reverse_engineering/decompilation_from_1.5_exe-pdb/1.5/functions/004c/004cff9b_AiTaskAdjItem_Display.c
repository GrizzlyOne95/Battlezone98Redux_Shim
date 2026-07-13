/*
 * Entry: 004cff9b
 * Name: AiTaskAdjItem::Display
 * Namespace: AiTaskAdjItem
 * Signature: void Display(AiTaskAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall AiTaskAdjItem::Display(AiTaskAdjItem *this)

{
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_58,"%s (%f)",aiTaskItems[this->var].name,(double)*aiTaskItems[this->var].current);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  return;
}
