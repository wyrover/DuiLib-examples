/*!
* \file Animator.cpp
* \brief 动画类库
*
* 动画类库实现
*
* \author wangyang
* \date 2015/02/15
* \version 1.0
*/

#include "stdafx.h"
#include "Animation/Animator.h"
#include <boost/foreach.hpp>
#include "cactus/cactus_zlogger.h"
namespace DuiLib
{

    //typedef boost::shared_ptr<IAnimator> IAnimatorPtr;
    typedef IAnimator* IAnimatorPtr;

    class AnimatorManagerImpl
    {
    public:
        AnimatorManagerImpl();
        ~AnimatorManagerImpl();
    public:
        void add_animator(IAnimatorPtr animator);
        void remove_animator(IAnimatorPtr animator);
        bool exist(IAnimatorPtr animator);
        void clear();
    private:
        void _run();
    private:
        std::list<IAnimatorPtr>             animator_list_;
        boost::shared_ptr<boost::thread>    thrd_;
        boost::recursive_mutex              mutex_;
        boost::mutex                        con_mutex_;
        boost::condition_variable           condition_;
    };

    typedef cactus::Singleton<AnimatorManagerImpl> AnimatorManager;

Animator::Animator() : paused_(true), running_(false), speed_(0), lost_pos_(0), new_pos_(0), repeat_(-1), reverse_(false)
{
    tweener_.addListener(this);
}

Animator::~Animator()
{
    TRACE_SEND_FORMAT("释放 Animator 对象，地址: %X", this);
    AnimatorManager::instance().remove_animator(this);
}

void Animator::start()
{
    if (! AnimatorManager::instance().exist(this)) {
        lost_pos_ = start_pos_;
        tweener_.removeAllTween();
        tween::TweenerParam param(1, speed_, quart_, easy_);
        param.repeat_ = repeat_;
        param.reverse_ = reverse_;
        param.addProperty(&lost_pos_, new_pos_);
        tweener_.addTween(param);
        paused_ = false;
        running_ = true;
        AnimatorManager::instance().add_animator(this);
		//ZLOG_DEBUG(_T("Animator::start()"));
    }
}

void Animator::cancel()
{
    this->end();
}

void Animator::end()
{
    running_ = false;
    AnimatorManager::instance().remove_animator(this);
}

bool Animator::is_running()
{
    return running_;
}

void Animator::set_tweener(int quart, int easy)
{
    quart_ = quart;
    easy_ = easy;
}

void Animator::set_repeat_count(int value)
{
    repeat_ = value;
}

void Animator::set_reverse(bool value)
{
    reverse_ = value;
}

void Animator::set_start_value(double value)
{
    start_pos_ = value;
}

void Animator::set_interval(float value)
{
    speed_ = value;
}

void Animator::set_end_value(double value)
{
    new_pos_ = value;
}

void Animator::pause()
{
    if (is_started() && !paused_) {
        paused_ = true;
    }
}

void Animator::resume()
{
    /*
    if (paused_) {
        paused_ = false;
        condition_.notify_all();
    }
    */
}

bool Animator::is_paused()
{
    return paused_;
}

bool Animator::is_started()
{
    return is_running();
}

void Animator::set_update_callback(TThreadMethod update_callback)
{
    update_callback_ = update_callback;
}

/*
void Animator::_run()
{
    while (TRUE) {
        DWORD startTime = GetTickCount();

        do {
            boost::this_thread::interruption_point();
            boost::mutex::scoped_lock lock(mutex_);

            if (paused_)
                condition_.wait(lock);

            running_ = true;
            this->tweener_.step(GetTickCount());

            if (update_callback_)
                TThread::Synchronize(update_callback_);
        } while ((GetTickCount() - startTime) < 33);
    }
}
*/

double Animator::get_value()
{
    return lost_pos_;
}

void Animator::onStart(const TweenerParam& param)
{
}

void Animator::onStep(const TweenerParam& param)
{
    if (running_ && update_callback_) {
        TThread::Synchronize(update_callback_);
    }
}

void Animator::onComplete(const TweenerParam& param)
{
    
    AnimatorManager::instance().remove_animator(this);

    if (complate_callback_)
        TThread::Synchronize(complate_callback_);

    running_ = false;
}

void Animator::set_complete_callback(TThreadMethod complete_callback)
{
    complate_callback_ = complete_callback;
}

void Animator::update(long currentMillis)
{
    if (running_) {
        this->tweener_.step(currentMillis);
    }
}

void Animator::set_name(LPCTSTR name)
{
    name_ = name;
}


AnimatorManagerImpl::AnimatorManagerImpl()
{
    boost::function0<void> f = boost::bind(&AnimatorManagerImpl::_run, this);
    thrd_.reset(new boost::thread(f));
    // Zebra::logger = new zLogger(_T("dg"), _T("DriverGenuis"));
    // Zebra::logger->setLevel(_T("all"));
}

AnimatorManagerImpl::~AnimatorManagerImpl()
{
    if (thrd_)
        thrd_->interrupt();
}

void AnimatorManagerImpl::add_animator(IAnimatorPtr animator)
{
    boost::recursive_mutex::scoped_lock lock(mutex_);
	//ZLOG_DEBUG(_T("1111animator_list_:size =%d "),animator_list_.size());
    animator_list_.push_back(animator);
	//ZLOG_DEBUG(_T("1111animator_list_:size =%d "),animator_list_.size());
	lock.unlock();
    condition_.notify_all();
	//OutputDebugString(_T("condition_.notify_all();"));
	condition_.notify_all();

}

void AnimatorManagerImpl::remove_animator(IAnimatorPtr animator)
{
    boost::recursive_mutex::scoped_lock lock(mutex_);

    for (list<IAnimatorPtr>::iterator it = animator_list_.begin(); it != animator_list_.end(); ++it) {
        IAnimatorPtr p = (*it);

        if (animator == p) {
            animator_list_.erase(it);
            ++it;
            break;
        }
    }

    lock.unlock();
}



bool AnimatorManagerImpl::exist(IAnimatorPtr animator)
{
    boost::recursive_mutex::scoped_lock lock(mutex_);
    list<IAnimatorPtr>::const_iterator it = std::find(animator_list_.begin(),
            animator_list_.end(), animator);
    lock.unlock();
    return (it != animator_list_.end());
}


void AnimatorManagerImpl::clear()
{
    boost::recursive_mutex::scoped_lock lock(mutex_);
    animator_list_.clear();    
    lock.unlock();
}

void AnimatorManagerImpl::_run()
{
    DWORD startTime = 0, tick = 0, frame = 10;
    while (TRUE) {
        startTime = GetTickCount();

        boost::this_thread::interruption_point();
        boost::mutex::scoped_lock lock(con_mutex_);

        if (animator_list_.size() == 0)
		{
			//ZLOG_DEBUG(_T("animator_list_.size() == 0"));
			condition_.wait(lock);
		}
            
		//ZLOG_DEBUG(_T("AnimatorManagerImpl::_run()"));

        boost::recursive_mutex::scoped_lock lock2(mutex_);
        std::list<IAnimatorPtr> animator_list2 = animator_list_;        
		//ZLOG_DEBUG(_T("animator_list2:size =%d "),animator_list2.size());
        lock2.unlock();

        BOOST_FOREACH(IAnimatorPtr animator, animator_list2) {
            if (exist(animator))
			{
				animator->update(GetTickCount());
			}
        }

        tick = GetTickCount() - startTime;
        if (tick < frame){
            //ZLOG_DEBUG(_T("animator:%d->%d "), tick, frame);
            ::Sleep(frame - tick);
        }
    }
}

void UILIB_API clear_animator()
{
    AnimatorManager::instance().clear();
}


} // namespace DuiLib