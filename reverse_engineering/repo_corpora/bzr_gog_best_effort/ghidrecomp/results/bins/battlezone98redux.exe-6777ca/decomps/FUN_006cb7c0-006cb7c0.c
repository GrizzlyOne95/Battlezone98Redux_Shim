
void __fastcall FUN_006cb7c0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852a3e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0xd;
  FUN_006cd250(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)(param_1 + 0x1bc));
  local_8._0_1_ = 0xc;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 400));
  local_8._0_1_ = 0xb;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x178));
  local_8._0_1_ = 10;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x160));
  local_8._0_1_ = 9;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x148));
  local_8._0_1_ = 8;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x130));
  local_8._0_1_ = 7;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x118));
  local_8._0_1_ = 6;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x100));
  local_8._0_1_ = 5;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0xe8));
  local_8._0_1_ = 4;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0xd0));
  local_8._0_1_ = 3;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0xb8));
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8._0_1_ = 1;
  FUN_006d0800();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006d0800();
  local_8 = 0xffffffff;
  FUN_006cfed0();
  ExceptionList = local_10;
  return;
}

