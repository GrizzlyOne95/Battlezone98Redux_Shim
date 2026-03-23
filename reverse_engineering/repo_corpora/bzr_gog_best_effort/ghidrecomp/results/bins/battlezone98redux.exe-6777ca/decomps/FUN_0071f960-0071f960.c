
CTraceSnapshot * __thiscall FUN_0071f960(CTraceSnapshot *param_1,uint param_2)

{
  CTraceSnapshot::~CTraceSnapshot(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

