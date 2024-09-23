#pragma once
#include <type_traits>
#include <utility>
#include <functional>

namespace hbreukers
{

template<typename OutType, typename InType>
class DataStream;

// template<typename T>
// class DataStreamInfo
// {
// public:
//     T* source;
// };

template<typename T, typename Process, typename MixinBase>
class DataStreamProcess : public MixinBase
{
    using ThisType = DataStreamProcess<T, Process, MixinBase>;
public:
    DataStreamProcess(const MixinBase& base, const Process& process):
    MixinBase(base),
    mProcess(process)
    {}    

    template<typename OutType>
    auto addDataStream()
    {
        return DataStream<OutType,ThisType>{};
    }

    template<typename SinkFunc>
    auto addDataSink(SinkFunc&& sinkFunc)
    {
        return DataStream<void,ThisType>{}.process(std::forward<SinkFunc>(sinkFunc));
    }
    

    auto update(auto&& in)
    {
        return std::invoke(mProcess,std::forward<decltype(in)>(in));
    }

    auto update()
    {
        return std::invoke(mProcess);
    }

private:

Process mProcess;
};


template<typename OutType, typename InStreamType>
class DataStream
{
    using ThisType = DataStream<OutType,InStreamType>;
public:
    // explicit DataStream(const DataStreamInfo<InStreamType>& dsi):
    // mDataStreamInfo(dsi)
    // {}

    template<typename Process>
    auto process([[maybe_unused]] Process&& process)
    {
        return DataStreamProcess<OutType,Process,ThisType>(*this,std::forward<Process>(process));
    }

private:
    // DataStreamInfo<InStreamType> mDataStreamInfo;

};

template<typename SourceFunc>
auto makeSource(SourceFunc&& sourceFunc)
{
    using RetType = std::invoke_result_t<SourceFunc>;
    return DataStream<RetType,void>{}.process(std::forward<SourceFunc>(sourceFunc));
}

}