
VirtualProcessorRoot * __thiscall FUN_006ae2c0(VirtualProcessorRoot *param_1,uint param_2)

{
  Concurrency::details::VirtualProcessorRoot::~VirtualProcessorRoot(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

