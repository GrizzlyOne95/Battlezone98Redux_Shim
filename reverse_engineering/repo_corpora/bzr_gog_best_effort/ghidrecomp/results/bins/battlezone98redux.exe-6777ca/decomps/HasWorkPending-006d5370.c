
/* Library Function - Single Match
    protected: virtual bool __thiscall Concurrency::details::SchedulerBase::HasWorkPending(void)
   
   Library: Visual Studio 2010 Debug */

bool __thiscall Concurrency::details::SchedulerBase::HasWorkPending(SchedulerBase *this)

{
  char cVar1;
  
  cVar1 = FUN_006d73e0();
  if ((cVar1 == '\0') && (cVar1 = FUN_006d7470(), cVar1 == '\0')) {
    return false;
  }
  return true;
}

