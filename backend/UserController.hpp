#ifndef USERCONTROLLER_HPP
# define USERCONTROLLER_HPP
#include <string>

class UserController
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