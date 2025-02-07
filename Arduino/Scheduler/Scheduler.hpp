/*
 * Scheduler.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef TASKS_SCHEDULER_HPP_
#define TASKS_SCHEDULER_HPP_
#include <avr/sleep.h>
#include <stdlib.h>
#include "Task.hpp"
#include "Mailbox.hpp"
#include "SchedulerDefines.hpp"

#define NUMBER_OF_SLOTS 8


enum TaskType
{
    TaskType_OneShot = 0,
    TaskType_Always,
    TaskType_Periodic
};

enum TaskActive
{
    TaskActiveTrue = true,
    TaskActiveFalse = false
};

// - This structure defines the Task Information
struct st_TaskInfo {
	Task * pTask;                       // - Pointer to the Task
	TaskType enTaskType;                // - Task type
	bool bTaskIsActive;                 // - True when the task is available
	uint64_t u64TickInterval;           // - How often the task is executed
	uint64_t u64Ticks;                  // - Current tick count
	uint64_t u64TickIntervalInitValue;  // - Value to reset
};



class Scheduler
{
public:
    Scheduler();
    SchedulerTypes::UInt64 m_u64ticks;
    SchedulerTypes::ErrorCodes attach(Task * i_pTask, TaskType i_enType, TaskActive i_enTaskActive, uint64_t i_u64TickInterval = 0U);
    SchedulerTypes::ErrorCodes run(void);
    SchedulerTypes::ErrorCodes setup(void);
    void Sleep();
private:
    SchedulerTypes::UInt8 m_u8OpenSlots; // - Available slots
    SchedulerTypes::UInt8 m_u8NextSlot;  // - Next available slot
    SchedulerTypes::UInt8 m_u8TaskCount; // - Number of tasks attached
    st_TaskInfo m_aSchedule[NUMBER_OF_SLOTS]; // - Current schedule to be executed
    st_TaskInfo m_aNextSchedule[NUMBER_OF_SLOTS]; // - Next schedule to be executed (not implemented)
    SchedulerTypes::ErrorCodes CalculateNextSchedule(void); // - Calculate next schedule tasks (not implemented)
    SchedulerTypes::ErrorCodes SortScheduleByPriority(Task * i_pSchedule); // - Sorts a schedule based on priority (not implemented)
    uintptr_t m_pNextSchedule; // - Pointer to the next schedule.
    Mailbox* m_pMailbox;
};



#endif /* TASKS_SCHEDULER_HPP_ */
