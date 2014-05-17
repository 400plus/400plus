/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef _STATE_OBJECT_H_
#define _STATE_OBJECT_H_

#include <string.h>

#include "firmware.h"

// with some help from ML here we have state objects
// they look the same in 400d

// state object related
typedef struct state_object * (*state_transition_function_t)(
		void * x,
		void * y,
		void * z,
		void * w
);

struct state_transition_struct {
	uint32_t			next_state;
	state_transition_function_t	state_transition_function;
};
typedef struct state_transition_struct state_transition_t;


struct state_object_struct {
	const char *		type;		// off 0x00, "StateObject"
	const char *		name;		// off 0x04, arg 0
	uint32_t		auto_sequence;	// off 0x08, arg 1

	// off 0x0c, always DefaultStateHandler ?
	void			(*state_object_handler)(
		struct state_object_struct *	self,
		void *				x,
		uint32_t			input,
		void *				z,
		void *				t
	);

	// Points to an array of size [max_inputs][max_states]
	state_transition_t *	state_matrix;	// off 0x10
	uint32_t		max_inputs;	// off 0x14, arg 2
	uint32_t		max_states;	// off 0x18, arg 3
	uint32_t		current_state;	// off 0x1c, initially 0
};
typedef struct state_object_struct state_object_t;

extern state_object_t * CreateStateObject(
	const char *		name,
	int			auto_sequence,
	state_transition_t *	state_matrix,
	int			max_inputs,
	int			max_states
);

// the matrix is all states for one input, then all states for next input, etc...
#define STATE_FUNC(stateobj,input,state) stateobj->state_matrix[(state) + (input) * stateobj->max_states].state_transition_function
#define STATE_NEXT(stateobj,input,state) stateobj->state_matrix[(state) + (input) * stateobj->max_states].next_state

static inline void state_object_matrix_copy_for_patching(state_object_t * so) {
	int size = so->max_inputs * so->max_states * sizeof(state_transition_t);
	state_transition_t * new_matrix = (state_transition_t *)AllocateMemory(size);
	memcpy(new_matrix, so->state_matrix, size);
	so->state_matrix = new_matrix;
}

static inline void state_object_install_hook(state_object_t * so, int input, int state, void* newfunc) {
	if ((uint32_t)(so->state_matrix) & 0xFF000000) // that's in ROM, make a copy to allow patching
		state_object_matrix_copy_for_patching(so);
	STATE_FUNC(so,input,state) = newfunc;
}

// some extra structs
typedef struct {
	const char *			identifier;             //~ off_0x00    "TaskClass"
	const char *			name;                   //~ off_0x04    task class name. ie: PropMgr
	int				off_0x08;               //~ unknown     initialized to 1 in CreateTaskClass
	const struct task *		task_struct_ptr;        //~ off_0x0c    ret_CreateTask (ptr to task struct) called from CreateTaskClass
	const struct msg_queue *	msg_queue_ptr_maybe;    //~ off_0x10    some kind of message queue pointer (very low level functions at work)
	void *				eventdispatch_func_ptr; //~ off_0x14    event dispatch pointer. ie: propmgrEventDispatch
} task_class_t;

typedef struct {
	char *			name;
	task_class_t *		task_class;
	state_object_t *	state_object;
	int 			debug_class;
	void *			unk_0x10;
	void *			pmgr_sync_event;
	void *			unk_0x18;
	void *			unk_0x1C;
	void *			unk_0x20;
	void *			ptp_sync_data_event_flag_struct;
	void *			unk_0x28;
	void *			unk_0x2C;
} manager_t;


#endif // _PTP_H_

