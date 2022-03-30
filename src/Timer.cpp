#include "Timer.h"

Timer::Timer(const Timeout &timeout)
    : _timeout(timeout)
{
}

Timer::Timer(const Timer::Timeout &timeout,
             const Timer::Interval &interval,
             bool singleShot)
    : _isSingleShot(singleShot),
      _interval(interval),
      _timeout(timeout)
{
}

void Timer::start(bool multiThread)
{
    if (this->running() == true)
        return;

    _running = true;

    if (multiThread == true) {
        _thread = std::thread(
                    &Timer::_temporize, this);
    }
    else{
        this->_temporize();
    }
}

void Timer::stop()
{
    _running = false;
    _thread.join();
}

bool Timer::running() const
{
    return _running;
}

void Timer::setSingleShot(bool singleShot)
{
    if (this->running() == true)
       return;

    _isSingleShot = singleShot;
}

bool Timer::isSingleShot() const
{
    return _isSingleShot;
}

void Timer::setInterval(const Timer::Interval &interval)
{
    if (this->running() == true)
       return;

    _interval = interval;
}

const Timer::Interval &Timer::interval() const
{
    return _interval;
}

void Timer::setTimeout(const Timeout &timeout)
{
    if (this->running() == true)
       return;

    _timeout = timeout;
}

const Timer::Timeout &Timer::timeout() const
{
    return _timeout;
}

void Timer::_temporize()
{
    if (_isSingleShot == true) {
        this->_sleepThenTimeout();
    }
    else {
        while (this->running() == true) {
            this->_sleepThenTimeout();
        }
    }
}

void Timer::_sleepThenTimeout()
{
    std::this_thread::sleep_for(_interval);

    if (this->running() == true)
        this->timeout()();
}
