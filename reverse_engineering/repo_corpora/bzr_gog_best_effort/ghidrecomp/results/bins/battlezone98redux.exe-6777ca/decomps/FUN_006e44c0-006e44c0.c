
CParkingWnd * __thiscall FUN_006e44c0(CParkingWnd *param_1,uint param_2)

{
  CParkingWnd::~CParkingWnd(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

