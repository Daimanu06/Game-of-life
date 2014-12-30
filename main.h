#ifndef MAIN_H
#define MAIN_H

#include <string>

namespace gameoflife {
	class Renderer;
}

/**
 * @brief hub
 *
 * Read the arguments and make an action accordingly.
 */
void arguments_hub(int, char **);

/**
 * @brief print_help
 * @param exename The name of the executable shown in the message.
 *
 * Prints a help message that display a short description and how to use the software.
 */
void print_help    (const std::string &);

/**
 * @brief print_version
 * @param exename The name of the executable shown in the message.
 *
 * Print the version of the software and the author(s) name(s)
 */
void print_version (const std::string &);

/**
 * @brief start_game
 *
 * Launch the game if no other arguments (like help or version) can prevent it.
 */
void start_game    (gameoflife::Renderer &);

#endif // MAIN_H

