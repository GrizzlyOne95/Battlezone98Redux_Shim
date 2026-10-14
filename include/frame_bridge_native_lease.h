#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cmath>

namespace BZROpenShim::FrameBridge
{
    struct NativeGeometryLeaseState
    {
        std::uint32_t magic=0x314c474e, version=2, byteSize=80, producerPid=0;
        std::int32_t ready=0;
        std::uint32_t missionGeneration=0;
        std::uint64_t revision=0, payloadHash=0, validFromQpc=0, qpcFrequency=0;
        std::uint32_t triangles=0;
        float towardSun[3]{}; // Ogre world coordinates, opposite Light direction.
        std::uint32_t sunValid=0;
        std::int32_t refreshRequested=0;
    };
    static_assert(sizeof(NativeGeometryLeaseState)==80);
    static_assert(offsetof(NativeGeometryLeaseState,ready)==16);
    static_assert(offsetof(NativeGeometryLeaseState,refreshRequested)==76);
    inline bool ValidTerrainSun(const float* direction)
    {
        const float lengthSquared=direction[0]*direction[0]+direction[1]*direction[1]+direction[2]*direction[2];
        return std::isfinite(lengthSquared)&&std::abs(lengthSquared-1)<1e-4f;
    }
    inline bool NativeLeaseMatchesFrame(const NativeGeometryLeaseState& lease,std::uint32_t pid,
        std::uint64_t observationQpc,std::uint64_t captureQpc,std::uint64_t frequency)
    {
        return lease.magic==0x314c474e&&lease.version==2&&lease.byteSize==80&&lease.producerPid==pid&&
            lease.ready==1&&lease.revision&&lease.triangles&&lease.triangles<=1000000&&lease.validFromQpc&&
            lease.qpcFrequency==frequency&&frequency&&observationQpc>=lease.validFromQpc&&captureQpc>=observationQpc;
    }
}

#ifdef _WIN32
#include <Windows.h>
#include <string>
namespace BZROpenShim::FrameBridge
{
    // Header fields use a named mutex; Ready and refresh control use Win32
    // interlocked operations. Readers never wait on a busy producer. Dirty
    // invalidation does not acquire the mutex and always clears Ready first.
    class NativeGeometryLease
    {
    public:
        ~NativeGeometryLease() { Close(); }
        NativeGeometryLease()=default;
        NativeGeometryLease(const NativeGeometryLease&)=delete;
        NativeGeometryLease& operator=(const NativeGeometryLease&)=delete;
        bool Open(std::uint32_t pid,bool publisher)
        {
            if(state_) return pid==pid_&&publisher==publisher_;
            const auto name=L"Local\\OpenShim.NativeGeometry.v2."+std::to_wstring(pid);
            mutex_=publisher?CreateMutexW(nullptr,FALSE,(name+L".Mutex").c_str()):OpenMutexW(SYNCHRONIZE|MUTEX_MODIFY_STATE,FALSE,(name+L".Mutex").c_str());
            if(!mutex_) { Close(); return false; }
            mapping_=publisher?CreateFileMappingW(INVALID_HANDLE_VALUE,nullptr,PAGE_READWRITE,0,sizeof(NativeGeometryLeaseState),name.c_str()):OpenFileMappingW(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,name.c_str());
            if(!mapping_) { Close(); return false; }
            state_=static_cast<NativeGeometryLeaseState*>(MapViewOfFile(mapping_,FILE_MAP_READ|FILE_MAP_WRITE,0,0,sizeof(NativeGeometryLeaseState)));
            if(!state_) { Close(); return false; }
            pid_=pid; publisher_=publisher;
            if(publisher_) Invalidate();
            return true;
        }
        void Invalidate() { if(state_&&publisher_) InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_->ready),0); }
        bool Publish(NativeGeometryLeaseState value)
        {
            if(!state_||!publisher_) return false;
            const DWORD lock=WaitForSingleObject(mutex_,0);
            if(lock!=WAIT_OBJECT_0&&lock!=WAIT_ABANDONED) return false;
            Invalidate(); value.ready=0; value.refreshRequested=0;
            // Do not erase a concurrently requested refresh while publishing.
            std::memcpy(state_,&value,offsetof(NativeGeometryLeaseState,refreshRequested));
            InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_->ready),1);
            ReleaseMutex(mutex_); return true;
        }
        bool Read(NativeGeometryLeaseState& value)
        {
            if(!state_) return false;
            const DWORD lock=WaitForSingleObject(mutex_,0);
            if(lock!=WAIT_OBJECT_0&&lock!=WAIT_ABANDONED) return false;
            if(lock==WAIT_ABANDONED) {
                InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_->ready),0);
                ReleaseMutex(mutex_); return false;
            }
            bool ready=InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&state_->ready),0,0)==1;
            if(ready) std::memcpy(&value,state_,offsetof(NativeGeometryLeaseState,refreshRequested));
            ready=ready&&InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&state_->ready),0,0)==1;
            value.ready=ready?1:0; value.refreshRequested=0;
            ReleaseMutex(mutex_); return ready;
        }
        void RequestRefresh() { if(state_&&!publisher_) InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_->refreshRequested),1); }
        bool TakeRefreshRequest() { return state_&&publisher_&&InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_->refreshRequested),0)!=0; }
        void Close()
        {
            Invalidate(); if(state_)UnmapViewOfFile(state_); state_=nullptr;
            if(mapping_)CloseHandle(mapping_); mapping_=nullptr;
            if(mutex_)CloseHandle(mutex_); mutex_=nullptr; pid_=0; publisher_=false;
        }
    private:
        HANDLE mapping_=nullptr,mutex_=nullptr;
        NativeGeometryLeaseState* state_=nullptr;
        std::uint32_t pid_=0;
        bool publisher_=false;
    };
}
#endif
