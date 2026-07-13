
/* Library Function - Multiple Matches With Same Base Name
    public: virtual bool __thiscall Concurrency::multi_link_registry<class
   Concurrency::ISource<unsigned int> >::remove(class Concurrency::ISource<unsigned int> *)
    public: virtual bool __thiscall Concurrency::multi_link_registry<class Concurrency::ISource<enum
   Concurrency::agent_status> >::remove(class Concurrency::ISource<enum Concurrency::agent_status>
   *)
    public: virtual bool __thiscall Concurrency::multi_link_registry<class
   Concurrency::ITarget<unsigned int> >::remove(class Concurrency::ITarget<unsigned int> *)
    public: virtual bool __thiscall Concurrency::multi_link_registry<class Concurrency::ITarget<enum
   Concurrency::agent_status> >::remove(class Concurrency::ITarget<enum Concurrency::agent_status>
   *)
   
   Library: Visual Studio */

int __cdecl remove(char *_Filename)

{
  uint in_EAX;
  uint uVar1;
  
  if (_Filename == (char *)0x0) {
    uVar1 = in_EAX & 0xffffff00;
  }
  else {
    uVar1 = FUN_005fad00(_Filename);
  }
  return uVar1;
}

