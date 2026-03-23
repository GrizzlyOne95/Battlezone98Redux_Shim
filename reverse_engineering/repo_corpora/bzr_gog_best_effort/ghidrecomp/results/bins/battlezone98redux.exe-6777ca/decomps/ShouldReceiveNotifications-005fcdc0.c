
/* Library Function - Single Match
    public: bool __thiscall Concurrency::details::SchedulerProxy::ShouldReceiveNotifications(void)
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

bool __thiscall
Concurrency::details::SchedulerProxy::ShouldReceiveNotifications(SchedulerProxy *this)

{
  return *(int *)(this + 0xe4) == *(int *)(this + 0xec);
}

