
void __fastcall FUN_00704e10(CXMLParser *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856d88;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0070f820(param_1);
  local_8 = 0xffffffff;
  CXMLParser::~CXMLParser(param_1);
  ExceptionList = local_10;
  return;
}

