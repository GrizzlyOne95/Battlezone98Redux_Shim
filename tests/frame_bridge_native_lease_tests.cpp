#include "frame_bridge_native_lease.h"
#include "test_check.h"
#include <string>
#include <cstdlib>
using namespace BZROpenShim::FrameBridge;
using OpenShimTest::Require;
#ifdef _WIN32
static void ChildRead(DWORD pid,bool expected)
{
    wchar_t exe[MAX_PATH]{}; Require(GetModuleFileNameW(nullptr,exe,MAX_PATH)>0,"lease test executable path");
    std::wstring command=L"\""+std::wstring(exe)+L"\" --read "+std::to_wstring(pid)+(expected?L" 1":L" 0");
    STARTUPINFOW startup{}; startup.cb=sizeof(startup); PROCESS_INFORMATION process{};
    Require(CreateProcessW(nullptr,command.data(),nullptr,nullptr,FALSE,CREATE_NO_WINDOW,nullptr,nullptr,&startup,&process)!=FALSE,"spawn lease reader process");
    Require(WaitForSingleObject(process.hProcess,5000)==WAIT_OBJECT_0,"bounded lease reader completion");
    DWORD code=1; GetExitCodeProcess(process.hProcess,&code); CloseHandle(process.hThread); CloseHandle(process.hProcess);
    Require(code==0,"cross-process lease read/decline");
}
#endif
int main(int argc,char** argv)
{
#ifdef _WIN32
    if(argc==4&&std::string(argv[1])=="--read") {
        const auto pid=static_cast<DWORD>(std::strtoul(argv[2],nullptr,10)); const bool expected=std::string(argv[3])=="1";
        NativeGeometryLease reader; NativeGeometryLeaseState state{};
        const bool actual=reader.Open(pid,false)&&reader.Read(state);
        Require(actual==expected,"child lease ready state");
        if(actual) Require(NativeLeaseMatchesFrame(state,pid,100,110,1000),"child lease frame identity");
        return OpenShimTest::ExitCode();
    }
#else
    (void)argc; (void)argv;
#endif
    NativeGeometryLeaseState lease; lease.producerPid=7; lease.ready=1; lease.revision=1; lease.payloadHash=42;
    lease.validFromQpc=100; lease.qpcFrequency=1000; lease.triangles=2;
    Require(NativeLeaseMatchesFrame(lease,7,100,110,1000),"valid live native frame lease");
    Require(!NativeLeaseMatchesFrame(lease,8,100,110,1000),"foreign PID rejected");
    Require(!NativeLeaseMatchesFrame(lease,7,99,110,1000),"camera predating snapshot rejected");
    Require(!NativeLeaseMatchesFrame(lease,7,100,99,1000),"capture before camera rejected");
    Require(!NativeLeaseMatchesFrame(lease,7,100,110,999),"clock domain mismatch rejected");
    for(int fault=0;fault<7;++fault) {
        auto bad=lease;
        if(fault==0)bad.ready=0; if(fault==1)bad.revision=0; if(fault==2)bad.byteSize=0;
        if(fault==3)bad.triangles=1000001; if(fault==4)bad.validFromQpc=0; if(fault==5)bad.magic=0; if(fault==6)bad.version=1;
        Require(!NativeLeaseMatchesFrame(bad,7,100,110,1000),"invalid live native lease rejected");
    }
    float sun[3]={0,1,0}; Require(ValidTerrainSun(sun),"unit world sun direction accepted");
    sun[1]=2; Require(!ValidTerrainSun(sun),"scaled sun rejected");
    sun[1]=NAN; Require(!ValidTerrainSun(sun),"nonfinite sun rejected");
    lease.towardSun[1]=1; lease.sunValid=1;
#ifdef _WIN32
    const auto pid=GetCurrentProcessId(); lease.producerPid=pid;
    NativeGeometryLease publisher,reader;
    Require(publisher.Open(pid,true)&&reader.Open(pid,false),"open named native lease");
    ChildRead(pid,false); Require(publisher.Publish(lease),"publish native lease"); ChildRead(pid,true);
    NativeGeometryLeaseState read{}; Require(reader.Read(read)&&read.revision==1&&read.sunValid==1&&read.towardSun[1]==1,"read stable revision and sunlight");
    reader.RequestRefresh(); Require(publisher.TakeRefreshRequest()&&!publisher.TakeRefreshRequest(),"refresh request consumed once");
    const auto name=L"Local\\OpenShim.NativeGeometry.v2."+std::to_wstring(pid)+L".Mutex";
    HANDLE mutex=OpenMutexW(SYNCHRONIZE|MUTEX_MODIFY_STATE,FALSE,name.c_str());
    Require(mutex&&WaitForSingleObject(mutex,0)==WAIT_OBJECT_0,"hold publication mutex");
    ChildRead(pid,false); publisher.Invalidate(); // Independent of busy reader/writer lock.
    ReleaseMutex(mutex); CloseHandle(mutex); ChildRead(pid,false);
    lease.revision=2; Require(publisher.Publish(lease),"republish fresh revision"); ChildRead(pid,true);
    publisher.Close(); ChildRead(pid,false); // Reader mapping survives, Ready does not.
#endif
    return OpenShimTest::ExitCode();
}
