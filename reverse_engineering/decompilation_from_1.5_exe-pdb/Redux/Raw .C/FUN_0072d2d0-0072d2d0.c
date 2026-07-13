
_RunAllParam<unsigned_char> * __thiscall
FUN_0072d2d0(_RunAllParam<unsigned_char> *param_1,uint param_2)

{
  Concurrency::details::_RunAllParam<unsigned_char>::~_RunAllParam<unsigned_char>(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

