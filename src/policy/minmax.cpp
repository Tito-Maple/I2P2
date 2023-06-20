#include <cstdlib>

#include "../state/state.hpp"
#include "./minmax.h"


/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
int MinMax::Minmax(State* state, int depth, int alpha, int beta, bool maxPlayer) {
	if (!state->legal_actions.size())
		state->get_legal_actions();
	if (maxPlayer) {
		if (depth == 0)
			return state->evaluate();
		if (state->game_state == WIN) {
			return state->evaluate() + 600;
		}
		int maximum = -1000000000;
		for (auto& cur : state->legal_actions) {
			State* st = state->next_state(cur);
			maximum = std::max(maximum, Minmax(st, depth - 1, alpha, beta, false));
			alpha = std::max(alpha, maximum);
			if (beta <= alpha)
				break;
		}
		return maximum;
	}
	else {
		int minimum = 1000000000;
		State* state2 = new State(state->board, 1 - state->player);
		if (depth == 0)
			return state2->evaluate();
		if (state->game_state == WIN) {
			return state2->evaluate() - 600;
		}
		for (auto& cur : state->legal_actions) {
			State* st = state->next_state(cur);
			minimum = std::min(minimum, Minmax(st, depth - 1, alpha, beta, true));
			beta = std::min(beta, minimum);
			if (beta <= alpha)
				break;
		}
		return minimum;
	}
}