#ifndef _state
#define _state

namespace State {

	static enum State {
		initialstate,
		letter,
		digit,
		blank,
		dash,
		comment,
		colon,
		state_7,
		state_8,
		state_9,
		state_10,
		id,
		intliteral,
		emptyspace,
		plusop,
		commentend,
		assignop,
		comma,
		semicolon,
		lparen,
		rparen,
		minusop,
		error,
		actionsymbol
	};

	static const int FINAL_STATE_INDEX = 11;
	
}


#endif