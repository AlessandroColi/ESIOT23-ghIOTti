#ifndef __TASK__
#define __TASK__

class Task 
{
    public: 
        Task() 
        {
            active = false;
        }

        /* periodic */
        virtual void init(int period) 
        {
            this->period = period;
            this->periodic = true;
            this->active = true;
            timeElapsed = 0;
        }

        /* aperiodic */
        virtual void init() 
        {
            this->periodic = false;
            this->active = true;
            timeElapsed = 0;
            this->completed = false;
        }

        virtual void tick() = 0;

        bool updateAndCheckTime(int basePeriod) 
        {
            timeElapsed += basePeriod;
            if (timeElapsed >= this->period) 
            {
                timeElapsed = 0;
                return true;
            } else 
            {
                return false;
            }
        }

        void setPeriod(int period)
        {
            this->period = period;
        }

        virtual void setActive() 
        {
            this->active = true;
            timeElapsed = 0;
        } 

        void setCompleted() 
        {
            this->completed = true;
            this->active = false;
        }

        bool isActive() 
        {
            return this->active;
        }

        bool isCompleted() 
        {
            return this->completed;
        }

        bool isPeriodic() 
        {
            return this->periodic;
        }

    private:
        int period;
        int timeElapsed;
        bool active;
        bool periodic;
        bool completed;
};

#endif