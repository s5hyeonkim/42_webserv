#ifndef REPOSITORY_HPP
# define REPOSITORY_HPP
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>

// 객체 생성 없이 싱글톤으로 작성하기;
class Repository
{
	private:
		//db
		std::vector<std::list<std::pair<std::string, std::string>>>	comments;
		std::map<std::string, int>									user_id;
		std::queue<int>												rest_ids;
	public:
		Repository(/* args */);
		~Repository();
};

Repository::Repository(/* args */) {}
Repository::~Repository() {}

#endif