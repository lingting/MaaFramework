#pragma once

#include "MinicapBase.h"

#include <atomic>
#include <thread>

MAA_CTRL_UNIT_NS_BEGIN

class MinicapStream : public MinicapBase
{
public:
    virtual ~MinicapStream() override;

public: // from UnitBase
    virtual bool parse(const json::value& config) override;

public: // from ScreencapAPI
    virtual bool init(int swidth, int sheight) override;

    virtual std::optional<cv::Mat> screencap() override;

private:
    bool read_until(size_t size);
    bool take_out(void* out, size_t size);
    void working_thread();

    Argv forward_argv_;

    std::atomic_bool working_ = false;
    std::mutex mutex_;
    cv::Mat image_;

    std::string buffer_;
    bool quit_ = true;
    std::thread pull_thread_;

    std::shared_ptr<IOHandler> process_handle_;
    std::shared_ptr<IOHandler> stream_handle_;
};

MAA_CTRL_UNIT_NS_END
