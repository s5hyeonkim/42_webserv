#ifndef ACONTROLLER_HPP
# define ACONTROLLER_HPP
# include <string>

// HTTP 요청과 응답을 처리하고 클라이언트와 상호작용하는 역할을 한다.
// 사용자(유빈이 소켓) 요청을 받아서 Service 클래스를 호출하고, Service의 응답을 클라이언트에게 반환(여기선 유빈이에게 반환)
class AController
{
    private:
        /* data */
    public:
        AController(/* args */);
        ~AController();
        void    handleRequestForm(std::string req);
};

AController::AController(/* args */) {}

AController::~AController() {}

void    AController::handleRequestForm(std::string req){
}

#endif