#ifndef SERVICE_HPP
# define SERVICE_HPP
# include <string>

// Service는 비즈니스 로직을 처리하고 제어. Repository를 활요하여 db와 상호작용.
class Service
{
    private:
        /* data */
    public:
        Service(std::string request);
        ~Service();
};

Service::Service(std::string) { 

}

Service::~Service() { }


#endif