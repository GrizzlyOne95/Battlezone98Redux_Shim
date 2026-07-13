
CMemoryDC * __thiscall FUN_0071b550(CMemoryDC *param_1,uint param_2)

{
  AfxRibbonCollector::CMemoryDC::~CMemoryDC(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

