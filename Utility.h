
#ifndef UTILITY_H_
#define UTILITY_H_
#include <exception>
/**
 * Define some utility class or function using in the assignemnt
 */
struct ListEmptyException : public std::exception
{
    const char* what() const throw ()
    {
        return "This is empty. Can not do this action";
    }
};
#endif /* UTILITY_H_ */
