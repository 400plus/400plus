/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef _STATE_OBJECT_H_
#define _STATE_OBJECT_H_

// with some help from ML here we have state objects
// they look the same in 400d

typedef struct state_object_struct * (*state_transition_function_t)(
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

#endif // _PTP_H_

