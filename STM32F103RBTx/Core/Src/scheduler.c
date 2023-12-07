/*
 * scheduler.c
 *
 *  Created on: Dec 7, 2023
 *      Author: HP
 */


#include "scheduler.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"


struct sTask{
	struct sTask *left, *right;
	void (*funcPointer)();
	uint32_t Delay;
	uint32_t Period, taskID;
	uint8_t RunMe;
}*TasksLinkedList = 0;

#define SCH_MAX_TASKS 40
#define LOCK 100
#define UNLOCK 200

uint8_t task_position[SCH_MAX_TASKS];
uint8_t lock = UNLOCK;


void UpdateTaskPosition(struct sTask *updateTask){
	if(updateTask == TasksLinkedList){
		return;
	}
	struct sTask *it = TasksLinkedList;
	uint8_t check = 0;
	while(it->Delay <= updateTask->Delay){
		if(it == TasksLinkedList) check += 1;
		if(check == 2) break;
		updateTask->Delay -= it->Delay;
		it = it->right;
	}

	//Insert to appropriate position
	if(updateTask->Delay <= 0) updateTask->RunMe = 1;
	updateTask->right = it;
	updateTask->left = it->left;
	it->left->right = updateTask;
	it->left = updateTask;

	//Update
	// Task is update to lowest
	if(check == 0){
			it->Delay -= updateTask->Delay;
			if(it->Delay <= 0) it->RunMe = 1;
			TasksLinkedList = updateTask;
	}
	// Task is update to middle
	else if (check == 1){
			it->Delay -= updateTask->Delay;
			if(it->Delay <= 0) it->RunMe = 1;
	}
	// Do nothing when task is update to highest
}

void SCH_Add_Task(void (*funcPointer)(), uint32_t Delay, uint32_t Period){
	if(!funcPointer){
		return ;
	}
	uint32_t runnerID = 0;
	while((runnerID < SCH_MAX_TASKS) && (task_position[runnerID])){
		runnerID += 1;
	}
	if(runnerID == SCH_MAX_TASKS){
		return -1;
	}else task_position[runnerID] = 1;
	lock = LOCK;
	struct sTask *curTask = (struct sTask*)malloc(sizeof(struct sTask));
	curTask->Delay = Delay;
	curTask->Period = Period;
	curTask->funcPointer = funcPointer;
	curTask->taskID = runnerID;
	curTask->RunMe = 0;
	if(TasksLinkedList){
		UpdateTaskPosition(curTask);
	}else{
		curTask->left = curTask;
		curTask->right = curTask;
		TasksLinkedList = curTask;
	}
	lock = UNLOCK;
}

void SCH_Update(){
	if((TasksLinkedList) && (!TasksLinkedList->RunMe) && (lock == UNLOCK)){
		if(TasksLinkedList->Delay > 0) TasksLinkedList->Delay -= 1;
		if(TasksLinkedList->Delay <= 0) TasksLinkedList->RunMe = 1;
	}
}

void SCH_Dispatch_Tasks(){
	lock = LOCK;
	while((TasksLinkedList) && (TasksLinkedList->RunMe)){
		(*TasksLinkedList->funcPointer)();
//		One shot task
		if(TasksLinkedList->Period == 0){
			struct sTask *toDelete = TasksLinkedList;
			TasksLinkedList = TasksLinkedList->right;
			SCH_Delete_Task(toDelete->taskID);
		}else{
//		Period task
			struct sTask *toFind = TasksLinkedList;
			TasksLinkedList->right->left = TasksLinkedList->left;
			TasksLinkedList->left->right = TasksLinkedList->right;
			TasksLinkedList = TasksLinkedList->right;
			toFind->RunMe = 0;
			toFind->Delay = toFind->Period;
			UpdateTaskPosition(toFind);
		}
	}
	lock = UNLOCK;
}

void SCH_Delete_Task(uint32_t index){
	if(task_position[index]){
		task_position[index] = 0;
		struct sTask *it = TasksLinkedList;
		while(it->taskID != index){
			it = it->right;
		}
		it->right->left = it->left;
		it->left->right = it->right;
		free(it);
	}
}
