
bool __fastcall FUN_006d1fe0(SchedulerBase *param_1)

{
  char cVar1;
  bool bVar2;
  
  cVar1 = FUN_006d54f0();
  if (cVar1 == '\0') {
    bVar2 = false;
  }
  else {
    bVar2 = Concurrency::details::SchedulerBase::HasWorkPending(param_1);
  }
  return bVar2;
}

