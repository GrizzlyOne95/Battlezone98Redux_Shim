
CXMLParser * __thiscall FUN_006b2b80(CXMLParser *param_1,uint param_2)

{
  CXMLParser::~CXMLParser(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

