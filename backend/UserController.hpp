#ifndef USERCONTROLLER_HPP
# define USERCONTROLLER_HPP
#include <string>
#include "AController.hpp"

class UserController : AController
{
	private:
	    /* data */
	public:
		UserController(/* args */);
		~UserController();
		void	handleRequestForm(std::string req);
};

UserController::UserController(/* args */)
{
}

UserController::~UserController()
{
}

void	UserController::handleRequestForm(std::string req)
{

}

#endif