/*
 * Entry: 004c7741
 * Name: DisplayInterface::PrintValue
 * Namespace: DisplayInterface
 * Signature: void PrintValue(DisplayInterface * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall DisplayInterface::PrintValue(DisplayInterface *this,char *param_1,char *param_2)

{
  char local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_48,"%s: %s",param_1,param_2);
  Font_Print_String(Default_Font,printBuffer,100,printHeight * printLine + 0x8c,local_48);
  printLine = printLine + 1;
  return;
}
